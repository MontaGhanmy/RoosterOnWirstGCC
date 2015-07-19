#include "ili9163.h"

void SetScrn(Colours8 Colour){
	uint16_t XCnt, YCnt;

	SetAddr(0, 0, XPix-1, YPix-1);

	for(XCnt = 0; XCnt<XPix; XCnt++){
		for(YCnt = 0; YCnt<YPix; YCnt++){
			switch(Colour){
			case Black:
				writeData16(0x0000);
				break;
			case Blue:
				writeData16(0x0010);
				break;
			case Red:
				writeData16(0x8000);
				break;
			case Magenta:
				writeData16(0x8010);
				break;
			case Green:
				writeData16(0x0400);
				break;
			case Cyan:
				writeData16(0x0410);
				break;
			case Yellow:
				writeData16(0x8400);
			case FlatBlue:
				writeData16(0x1DBF);
				break;
			case White:
				writeData16(0xFFFF);
				break;
			}
		}
	}
}
