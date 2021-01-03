#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <stdio.h>
#include <Windows.h>

using namespace std::chrono_literals;

std::wstring tetromino[7];
int nfieldWidth = 22;
int nfieldHeight = 27;
unsigned char *pField = nullptr;
int nScreenWidth = 120;
int nScreenHeight = 36;

int Rotate(int px, int py, int r)
{
	int pi = 0;
	switch (r % 4)
	{
	case 0: pi = py * 8 + px; break;
	case 1: pi = 56 + py - (px * 8); break;
	case 2: pi = 63 - (py * 8) - px; break;
	case 3: pi = 7 - py + (px * 8); break;
	}
	return pi;
}

bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY)
{
	for(int px = 0; px < 8; px++)
		for (int py = 0; py < 8; py++)
		{
			// index piece
			int pi = Rotate(px, py, nRotation);

			int fi = (nPosY + py) * nfieldWidth + (nPosX + px);

			if (nPosX + px >= 0 && nPosX + px < nfieldWidth)
			{
				if (nPosY + py >= 0 && nPosY + py < nfieldHeight)
				{
					if (tetromino[nTetromino][pi] != L'.' && pField[fi] != 0)
						return false; // fail on first it
				}
			}
		}
	return true;
}


int main()
{
	// tetris pieces
	tetromino[0].append(L"..XX....");
	tetromino[0].append(L"..XX....");
	tetromino[0].append(L"..XX....");
	tetromino[0].append(L"..XX....");
	tetromino[0].append(L"..XX....");
	tetromino[0].append(L"..XX....");
	tetromino[0].append(L"..XX....");
	tetromino[0].append(L"..XX....");

	tetromino[1].append(L"....XX..");
	tetromino[1].append(L"....XX..");
	tetromino[1].append(L"..XXXX..");
	tetromino[1].append(L"..XXXX..");
	tetromino[1].append(L"..XX....");
	tetromino[1].append(L"..XX....");
	tetromino[1].append(L"........");
	tetromino[1].append(L"........");

	tetromino[2].append(L"..XX....");
	tetromino[2].append(L"..XX....");
	tetromino[2].append(L"..XXXX..");
	tetromino[2].append(L"..XXXX..");
	tetromino[2].append(L"....XX..");
	tetromino[2].append(L"....XX..");
	tetromino[2].append(L"........");
	tetromino[2].append(L"........");

	tetromino[3].append(L"..XXXX..");
	tetromino[3].append(L"..XXXX..");
	tetromino[3].append(L"....XX..");
	tetromino[3].append(L"....XX..");
	tetromino[3].append(L"....XX..");
	tetromino[3].append(L"....XX..");
	tetromino[3].append(L"........");
	tetromino[3].append(L"........");

	tetromino[4].append(L"........");
	tetromino[4].append(L"........");
	tetromino[4].append(L"..XXXX..");
	tetromino[4].append(L"..XXXX..");
	tetromino[4].append(L"..XXXX..");
	tetromino[4].append(L"..XXXX..");
	tetromino[4].append(L"........");
	tetromino[4].append(L"........");

	tetromino[5].append(L"..XXXX..");
	tetromino[5].append(L"..XXXX..");
	tetromino[5].append(L"..XX....");
	tetromino[5].append(L"..XX....");
	tetromino[5].append(L"..XX....");
	tetromino[5].append(L"..XX....");
	tetromino[5].append(L"........");
	tetromino[5].append(L"........");
	
	tetromino[6].append(L"........");
	tetromino[6].append(L"........");
	tetromino[6].append(L"..XX....");
	tetromino[6].append(L"..XX....");
	tetromino[6].append(L"..XXXX..");
	tetromino[6].append(L"..XXXX..");
	tetromino[6].append(L"..XX....");
	tetromino[6].append(L"..XX....");

	// create playing field
	pField = new unsigned char[nfieldWidth * nfieldHeight]; 
	// board boundary
	for (int x = 0; x < nfieldWidth; x++) 
		for (int y = 0; y < nfieldHeight; y++)
			pField[y * nfieldWidth + x] = (x == 0 || x == nfieldWidth - 1 || y == nfieldHeight - 1) ? 9 : 0;

	// screen buffer
	wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];
	for (int i = 0; i < nScreenWidth*nScreenHeight; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	// Game Logic Details
	bool bGameOver = false;
	
	int nCurrentPiece = 1;
	int nCurrentRotation = 0;
	int nCurrentX = nfieldWidth / 2 - 2;
	int nCurrentY = 0;

	bool bKey[4];
	bool bKeyHold = false;
	
	int gSpeed = 40;
	int gSpdCount = 0;
	bool bFallDown = false;
	int nLineCount = 0;
	int nScore = 0;
	int nLevel = 0;
	
	std::vector<int> vLine;

	while (!bGameOver)
	{
		// GAME TIME
		std::this_thread::sleep_for(30ms);
		gSpdCount++;
		bFallDown = (gSpdCount == gSpeed);

		// USER INPUT
		for (int k = 0; k < 4; k++)
			bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28\x26"[k]))) != 0;

		// GAME LOGIC
		if (bKey[0])
		{
			nCurrentX += (!bKeyHold && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY)) ? 2 : 0;
			bKeyHold = true;
		}
		else if (bKey[1])
		{
			nCurrentX -= (!bKeyHold && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY)) ? 2 : 0;
			bKeyHold = true;
		}
		else if (bKey[2])
		{
			nCurrentY += (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1)) ? 1 : 0;
			
		}
		else if (bKey[3])
		{
			nCurrentRotation += (!bKeyHold && DoesPieceFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY)) ? 1 : 0;
			bKeyHold = true;
		}
		else bKeyHold = false;

		if (bFallDown)
		{
			if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
				nCurrentY++;
			else
			{
				// Lock piece 
				for (int px = 0; px < 8; px++)
					for (int py = 0; py < 8; py++)
					{
						if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] != L'.')
							pField[(nCurrentY + py) * nfieldWidth + (nCurrentX + px)] = nCurrentPiece + 1;
					}

				// check for complete lines
				for(int py = 0; py < 8; py++)
					if (nCurrentY + py < nfieldHeight - 1)
					{
						bool bLine = true;
						for (int px = 1; px < nfieldWidth - 1; px++)
							bLine &= (pField[(nCurrentY + py) * nfieldWidth + px]) != 0;

						if (bLine)
						{
							for (int px = 1; px < nfieldWidth - 1; px++)
								pField[(nCurrentY + py) * nfieldWidth + px] = 8;

							vLine.push_back(nCurrentY + py);
						}
					}

				nScore += 10;
				if (!vLine.empty()) nScore += (1 << vLine.size()) * 50;

				// choose next piece
				nCurrentX = nfieldWidth / 2 - 2; //TODO make random
				nCurrentY = 0;
				nCurrentRotation = 0;
				nCurrentPiece = rand() % 7;

				// if piece does not fit
				bGameOver = !DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);
			}
			gSpdCount = 0;
		}

		// RENDER OUTPUT    

		// draw field 
		for (int x = 0; x < nfieldWidth; x++)
			for (int y = 0; y < nfieldHeight; y++)
				screen[(y + 2) * nScreenWidth + (x + 2)] = L" ABCDEFG*#"[pField[y * nfieldWidth + x]];

		// draw current piece
		for (int px = 0; px < 8; px++)
			for (int py = 0; py < 8; py++)
			{
				if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] != L'.')
					screen[(nCurrentY + py + 2)*nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece + 65;
			}

		// draw score
		swprintf_s(&screen[2 * nScreenWidth + nfieldWidth + 6], 16, L"Score: %8d", nScore);
		swprintf_s(&screen[2 * nScreenWidth + nfieldWidth + 22], 16, L"Level: %8d", nLineCount);
 
		if (!vLine.empty())
		{
			// display frame
			WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
			std::this_thread::sleep_for(150ms);

			for (auto &v : vLine)
				for (int px = 1; px < nfieldWidth - 1; px++)
				{
					for (int py = v; py > 0; py--)
						pField[py * nfieldWidth + px] = pField[(py - 1) * nfieldWidth + px];
					pField[px] = 0;
				}
			vLine.clear();
			
			nLineCount++;
			gSpeed--;
		}
		nLevel = nLineCount;
		// display frame
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}

	CloseHandle(hConsole);
	std::cout << "Game Over! \n\n Your Score was " << nScore << " at level " << nLevel <<  std::endl;

	system("pause");


	return 0;
}