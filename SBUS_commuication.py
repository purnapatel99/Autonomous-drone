import numpy as np
packet = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
channels = [1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500]

packet[0] = np.uint8 (0x0F)
packet[1] = np.uint8 ((channels[0] & 0x07FF))
packet[2] = np.uint8 ((channels[0] & 0x07FF)>>8 | (channels[1] & 0x07FF)<<3)
packet[3] = np.uint8 ((channels[1] & 0x07FF)>>5 | (channels[2] & 0x07FF)<<6)
packet[4] = np.uint8 ((channels[2] & 0x07FF)>>2)
packet[5] = np.uint8 ((channels[2] & 0x07FF)>>10 | (channels[3] & 0x07FF)<<1)
packet[6] = np.uint8 ((channels[3] & 0x07FF)>>7 | (channels[4] & 0x07FF)<<4)
packet[7] = np.uint8 ((channels[4] & 0x07FF)>>4 | (channels[5] & 0x07FF)<<7)
packet[8] = np.uint8 ((channels[5] & 0x07FF)>>1)
packet[9] = np.uint8 ((channels[5] & 0x07FF)>>9 | (channels[6] & 0x07FF)<<2)
packet[10] = np.uint8 ((channels[6] & 0x07FF)>>6 | (channels[7] & 0x07FF)<<5)
packet[11] = np.uint8 ((channels[7] & 0x07FF)>>3)
packet[12] = np.uint8 ((channels[8] & 0x07FF))
packet[13] = np.uint8 ((channels[8] & 0x07FF)>>8 | (channels[9] & 0x07FF)<<3)
packet[14] = np.uint8 ((channels[9] & 0x07FF)>>5 | (channels[10] & 0x07FF)<<6)
packet[15] = np.uint8 ((channels[10] & 0x07FF)>>2)
packet[16] = np.uint8 ((channels[10] & 0x07FF)>>10 | (channels[11] & 0x07FF)<<1)
packet[17] = np.uint8 ((channels[11] & 0x07FF)>>7 | (channels[12] & 0x07FF)<<4)
packet[18] = np.uint8 ((channels[12] & 0x07FF)>>4 | (channels[13] & 0x07FF)<<7)
packet[19] = np.uint8 ((channels[13] & 0x07FF)>>1)
packet[20] = np.uint8 ((channels[13] & 0x07FF)>>9 | (channels[14] & 0x07FF)<<2)
packet[21] = np.uint8 ((channels[14] & 0x07FF)>>6 | (channels[15] & 0x07FF)<<5)
packet[22] = np.uint8 ((channels[15] & 0x07FF)>>3)
packet[23] = 0x00
packet[24] = 0x00

