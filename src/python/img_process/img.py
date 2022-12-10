from PIL import Image

im = Image.open("ZIM_pro.png").convert("RGB")
print(im.mode)
f = open('ZIMpro.txt','w+')
for x in range(im.size[0]):
    for y in range(im.size[1]):
        pix = im.getpixel((x,y))
        # print('0x', '%02X'%pix[0], '%02X'%pix[1], '%02X'%pix[2], '%02X'%pix[3], ',', x, ' ', y, file = f, sep="")
        # print('0x', '%02X'%pix[3], '%02X'%pix[0], '%02X'%pix[1], '%02X'%pix[2], ',', file = f, sep="")
        R = pix[0] >> 3
        G = pix[1] >> 2
        B = pix[2] >> 3

        rgb = (R << 11) | (G << 5) | B
        print('0x',  '%04X'%rgb, '%04X'%rgb, ',', file = f, sep="")
f.close()