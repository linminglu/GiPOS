#include "stdafx.h"
#include "EscPosCommands.h"
#include "BaseCodes.h"

EscPosCommands::EscPosCommands()
{
}


EscPosCommands::~EscPosCommands()
{
}


// std::size_t DefaultCharacterCommands::setRightSideCharacterSpacing(byte n)
// {
//     const byte command[3] = { BaseCodes::ESC, ' ', n };
//     return writeBytes(command, 3);
// }


std::size_t EscPosCommands::setCharacterSet(BaseCodes::CharacterSet charSet)
{
    const byte command[3] = { BaseCodes::ESC, 'R', charSet };
    return writeBytes(command, 3);
}


std::size_t EscPosCommands::setCharacterCodePage(BaseCodes::CodePage codePage)
{
    const byte command[3] = { BaseCodes::ESC, 't', codePage };
    return writeBytes(command, 3);
}


// std::size_t DefaultCharacterCommands::setPrintMode(byte modeByte)
// {
//     const byte command[3] = { BaseCodes::ESC, '!', modeByte };
//     return writeBytes(command, 3);
// }

/************************************************************************
黑白反显打印模式
************************************************************************/
std::size_t EscPosCommands::setInvert(bool enable)
{
    const byte command[3] = { BaseCodes::GS, 'B', enable };
    return writeBytes(command, 3);
}


std::size_t EscPosCommands::setUnderline(BaseCodes::TextUnderline underline)
{
    const byte command[3] = { BaseCodes::ESC, '-', underline };
    return writeBytes(command, 3);
}

/************************************************************************
加粗模式
************************************************************************/
std::size_t EscPosCommands::setEmphasis(bool enable)
{
    const byte command[3] = { BaseCodes::ESC, 'E', enable };
    return writeBytes(command, 3);
}


std::size_t EscPosCommands::setFont(BaseCodes::TextFont font)
{
    const byte command[3] = { BaseCodes::ESC, 'M', font };
    return writeBytes(command, 3);
}


std::size_t EscPosCommands::setColor(BaseCodes::TextColor color)
{
    const byte command[3] = { BaseCodes::ESC, 'r', color };
    return writeBytes(command, 3);
}

std::size_t EscPosCommands::setAlign(byte align)
{
    const byte command[3] = { BaseCodes::ESC,'a',align};
    return writeBytes(command, 3);
}
/************************************************************************
设置行间距为 [ n × 纵向或横向移动单位],默认移动单位为1像素
************************************************************************/
std::size_t EscPosCommands::setLineSpacing(byte n)
{
	const byte command[3] = { BaseCodes::ESC,'3',n};
	return writeBytes(command, 3);
}
// std::size_t DefaultCharacterCommands::setUpsideDown(bool enable)
// {
//     const byte command[3] = { BaseCodes::ESC, '{', enable };
//     return writeBytes(command, 3);
// }


std::size_t EscPosCommands::setCharacterSize(BaseCodes::TextMagnification horizontal,
                                                       BaseCodes::TextMagnification vertical)
{
    const byte command[3] = { BaseCodes::GS, '!', (horizontal << 4) | (vertical) };
    return writeBytes(command, 3);
}


std::size_t EscPosCommands::setCharacterSmoothing(bool enable)
{
    const byte command[3] = { BaseCodes::GS, 'b', enable };
    return writeBytes(command, 3);
}


// std::size_t DefaultCharacterCommands::setRotation(BaseCodes::TextRotate textRotate)
// {
//     const byte command[3] = { BaseCodes::ESC, 'V', textRotate };
//     return writeBytes(command, 3);
// }

std::size_t EscPosCommands::setAbusoluteLeft(int nOrgx)
{
	byte nL=nOrgx%256;
	byte nH=nOrgx/256;
	const byte command[4] = { BaseCodes::ESC, '$', nL, nH};
	return writeBytes(command, 4);
}
/************************************************************************
DLE EOT n 实时状态传送
        [格式] ASCII码 DLE EOT n
        十六进制码 10 04 n
        十进制码 16 4 n
        [范围] 1 ≤ n ≤ 4
        [描述] 根据下列参数，实时传送打印机状态，参数 n 用来指定所要传送的打印机状态：
        n = 1：传送打印机状态
        n = 2：传送脱机状态
        n = 3：传送错误状态
        n = 4：传送纸传感器状态
        [注释] 打印机收到该命令后立即返回相关状态
        该命令尽量不要插在2个或更多字节的命令序列中。
        即使打印机被ESC =(选择外设)命令设置为禁止，该命令依然有效。
        打印机传送当前状态，每一状态用1个字节数据表示。
        打印机传送状态时并不确认主机是否收到。
        打印机收到该命令立即执行。
        该命令只对串口打印机有效。打印机在任何状态下收到该命令都立即执行。
************************************************************************/
int EscPosCommands::queryStatus(byte n)
{
	const byte command[3] = { BaseCodes::DLE, BaseCodes::EOT, n};
	return writeBytes(command, 3);
}

std::size_t EscPosCommands::initialize()
{
	const byte command1[2] = { BaseCodes::ESC, 'S' };
	return writeBytes(command1, 2);
	//const byte command[2] = { BaseCodes::ESC, '@' };
	//return writeBytes(command, 2);
}

std::size_t EscPosCommands::openDrawer(byte nID,byte nOnTimes,byte nOffTimes)
{
	const byte command[5] = { BaseCodes::ESC, 'p',nID,nOnTimes,nOffTimes};
	return writeBytes(command, 5);
}

std::size_t EscPosCommands::cutPaper(BaseCodes::PaperCut type,byte numDotsToFeed)
{
	if (numDotsToFeed > 0)
	{
		const byte command[4] = { BaseCodes::GS, 'V', type + 'A', numDotsToFeed};
		return writeBytes(command, 4); // shift -> A/B
	}
	else
	{
		const byte command[3] = { BaseCodes::GS, 'V', type };
		return writeBytes(command, 3);
	}
}


/************************************************************************
打印bitmap图片
ESC * m nL nH d1...dk
************************************************************************/
std::size_t EscPosCommands::printImage(int left,const byte* bmp,int width,int height,int threshold)
{
	int numVerticalDots = 24;
	// width = nL + (nH * 256)
	// nH is the HIGH part of the WIDTH VALUE.
	// nL is the LOW part of the WIDTH VALUE.
	// nH will always be 0 for values less that 256 (1 byte)
	byte nH = (byte)((width>>8)&0xFF);
	byte nL = (byte)(width&0xFF);
	int bmpLen=width*height;

	std::size_t totalBytesWritten = 0;
	totalBytesWritten +=setLineSpacing(numVerticalDots);
	std::vector<byte> imageDataLine;

	for (int offset = 0; offset < height; offset += numVerticalDots)
	{
		setAbusoluteLeft(left);
		imageDataLine.clear();
		imageDataLine.push_back(BaseCodes::ESC);
		imageDataLine.push_back('*');
		imageDataLine.push_back(BaseCodes::RESOLUTION_24_DOTS_DOUBLE_DENSITY);
		imageDataLine.push_back(nL);
		imageDataLine.push_back(nH);

		for (int x = 0; x < width; ++x)
		{
			for (int k = 0; k < numVerticalDots/8; ++k)
			{
				byte slice = 0;
				for (int b = 0; b < 8; ++b)
				{
					int y = (offset + k*8) + b;
					int idx=x+y*height;
					boolean v = false;
					if (bmp[idx] <= threshold) {//black
						v=true;
					}
					slice |= (byte) ((v ? 1 : 0) << (7 - b));
				}
				imageDataLine.push_back(slice);
			}
		}
		imageDataLine.push_back(BaseCodes::LF);
		totalBytesWritten += writeBytes(&imageDataLine[0],imageDataLine.size());
	}

	return totalBytesWritten;
}
/************************************************************************
打印条码，固定ITF(交叉25码)
ESC * m nL nH d1...dk
************************************************************************/
std::size_t EscPosCommands::printBarcode(const char* barcode,int left,int width,int height)
{
	//设置条码高度
	byte command[3] = { BaseCodes::GS, 'h', 48};
	writeBytes(command, 3);
	//设置条码宽度
	byte command2[3] = { BaseCodes::GS, 'w', 4};
	writeBytes(command2, 3);
	//打印文字
// 	byte command3[3] = { BaseCodes::GS, 'H', '1'};
// 	writeBytes(command3, 3);
	setAbusoluteLeft(left);

	int len=strlen(barcode);
	std::vector<byte> buffer;
	buffer.push_back(BaseCodes::GS);
	buffer.push_back('k');
	buffer.push_back(5);//ITF
	for(int i=0;i<len;i++)
		buffer.push_back(barcode[i]);
	buffer.push_back(0);
	return writeBytes(&buffer[0],buffer.size());
}