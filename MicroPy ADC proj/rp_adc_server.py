# ADC DMA web server using MicroPython on Pico
#
# For detailed description, see https://iosoft.blog
#
# Copyright (c) 2021 Jeremy P Bentham
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# v0.14 JPB 10/11/21 Tidied up for release

import array, time, uctypes, math, random
import rp_devices as devs

ADC_CHAN = 0
ADC_PIN  = 26 + ADC_CHAN
ADC_SAMPLES = 1000
MIN_SAMPLES, MAX_SAMPLES = 10, 1000
ADC_RATE = 450000
MIN_RATE, MAX_RATE = 1000, 500000
DMA_CHAN = 0



adc = devs.ADC_DEVICE
dma_chan = devs.DMA_CHANS[DMA_CHAN]
dma = devs.DMA_DEVICE

parameters = {"nsamples":ADC_SAMPLES, "xrate":ADC_RATE, "simulate":0}

# Initialise ADC DMA
def adc_dma_init():
    pin = devs.GPIO_PINS[ADC_PIN]
    pad = devs.PAD_PINS[ADC_PIN]
    pin.GPIO_CTRL_REG = devs.GPIO_FUNC_NULL
    pad.PAD_REG = 0

    dma.CHAN_ABORT = 0xffff
    dma_chan.CTRL_TRIG_REG = 0

    adc.CS_REG = adc.FCS_REG = 0
    adc.CS.EN = 1
    adc.FCS.EN = adc.FCS.DREQ_EN = 1
    adc.FCS.THRESH = adc.FCS.OVER = adc.FCS.UNDER = 1
    adc.CS.AINSEL = ADC_CHAN

    dma_chan.READ_ADDR_REG = devs.ADC_FIFO_ADDR
    dma_chan.CTRL_TRIG_REG = 0
    dma_chan.CTRL_TRIG.CHAIN_TO = DMA_CHAN
    dma_chan.CTRL_TRIG.INCR_WRITE = dma_chan.CTRL_TRIG.IRQ_QUIET = 1
    dma_chan.CTRL_TRIG.TREQ_SEL = devs.DREQ_ADC
    dma_chan.CTRL_TRIG.DATA_SIZE = 1

# Discard any data in ADC FIFO
def flush_adc_fifo():
    dma_chan.CTRL_TRIG.EN = 0
    while adc.FCS.LEVEL:
        x = adc.FIFO_REG

# Capture ADC samples using DMA
def adc_capture():
    flush_adc_fifo()
    nsamp = max(MIN_SAMPLES, min(MAX_SAMPLES, parameters["nsamples"]))
    rate = max(MIN_RATE, min(MAX_RATE, parameters["xrate"]))
    adc_buff = array.array('H', (0 for _ in range(nsamp)))
    adc.DIV_REG = (48000000 // rate - 1) << 8
    dma_chan.WRITE_ADDR_REG = uctypes.addressof(adc_buff)
    dma_chan.TRANS_COUNT_REG = nsamp
    dma_chan.CTRL_TRIG.EN = 1
    adc.CS.START_MANY = 1
    while dma_chan.CTRL_TRIG.BUSY:
        time.sleep_ms(10)
    adc.CS.START_MANY = 0
    dma_chan.CTRL_TRIG.EN = 0
    return adc_buff

# EOF
