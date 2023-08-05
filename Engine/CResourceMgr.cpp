#include "CResourceMgr.h"
#include "CTexture.h"
#include "CShader.h"
#include "CMaterial.h"
#include "CGameObject.h"


CResourceMgr::CResourceMgr()
{
	LoadAnimationData();
}

CResourceMgr::~CResourceMgr()
{
	mAnimationDatas.clear();
	mResources.clear();
}

void CResourceMgr::LoadAnimationData()
{
	std::filesystem::path dataFilePath = L"..\\Data\\AnimationData.json";

	std::wifstream DataFile(dataFilePath);
	if (DataFile.is_open()) // 해당 파일이 존재하는 경우
	{
		std::wstring line;
		int idNum = 1;
		std::wstring objectName;
		while (std::getline(DataFile, line))
		{
			std::wstring aniId = L"\"id\": ";
			aniId += std::to_wstring(idNum);

			bool b2 = line.find(aniId);
			if (line.find(aniId) != std::string::npos)
			{
				AnimationData aniDesc;
				idNum++;
				std::getline(DataFile, line); // 하나의 id 내의 name 을 가져온다
				if (line.find(L"\"name\": ") != std::string::npos)
				{
					std::wstring aniName = line.substr(line.find(L"\"name\": ") + 9);
					aniName = aniName.substr(0, aniName.find(L",") - 1);
					aniDesc.name = aniName;
				}
				std::getline(DataFile, line);
				if (line.find(L"\"objectName\": ") != std::string::npos)
				{
					std::wstring objName = line.substr(line.find(L"\"objectName\": ") + 15);
					objName = objName.substr(0, objName.find(L",") - 1);
					aniDesc.objName = objName;
				}
				std::getline(DataFile, line);
				if (line.find(L"\"spriteNumber\": ") != std::string::npos);
				{
					size_t startPos = line.find(L"[") + 1;
					size_t endPos = line.find(L"]");
					std::wstring numStr = line.substr(startPos, endPos - startPos);

					// 문자열을 정수로 변환
					int spriteNum;
					swscanf_s(numStr.c_str(), L"%d", &spriteNum);
					aniDesc.spriteNum = spriteNum;
				}
				std::getline(DataFile, line);
				if (line.find(L"\"renderingMode\": ") != std::string::npos)
				{
					size_t startPos = line.find(L"[") + 1;
					size_t endPos = line.find(L"]");
					std::wstring numStr = line.substr(startPos, endPos - startPos);

					int renderModeNum;
					swscanf_s(numStr.c_str(), L"%d", &renderModeNum);
					aniDesc.renderingMode = (eRenderingMode)renderModeNum;
				}
				std::getline(DataFile, line);
				if (line.find(L"\"size\": ") != std::string::npos)
				{
					size_t startPos = line.find(L"[") + 1;
					size_t endPos = line.find(L"]");
					std::wstring numStr = line.substr(startPos, endPos - startPos);
					int sizeX, sizeY;
					swscanf_s(numStr.c_str(), L"%d, %d", &sizeX, &sizeY);

					aniDesc.size = Vector2((float)(sizeX * 1.0f), (float)(sizeY * 1.0f));
				}

				mAnimationDatas.push_back(aniDesc);
				int a = 0;
			}
		}
	}
}

void CResourceMgr::CreateAtlas(const std::wstring& spriteName, int spriteNum)
{
	std::shared_ptr<CTexture> atlasTex = std::make_shared<CTexture>(); // 최종 아틀라스 텍스쳐

	bool isMade = false; // 아틀라스 이미지의 처음 규격 생성 여부
	std::filesystem::path Path = L"..\\Resource\\Texture\\Animation\\";
	Path += spriteName;  // 폴더명
	Path += L"\\";
	Path += spriteName;  // 폴더명과 같은 각 sprite 의 공통된 이름
	Path += L"_";

	ScratchImage atlasImage;
	size_t atlasImageWidth;
	size_t atlasImageHeight;

	for (int i = 0; i < spriteNum; i++)
	{
		CTexture* tex = new CTexture; // 각 Sprite 가 담길 
		std::filesystem::path path = Path;
		path += std::to_wstring(i + 1);
		std::wstring sn = spriteName + L"_";
		sn += std::to_wstring(i + 1);
		path += L".png";
		HRESULT hr = tex->ResourceLoad(sn, path);
		if (hr == S_OK)
		{
			if (isMade == false)
			{
				atlasImageWidth = (tex->GetWidth()) * spriteNum;
				atlasImageHeight = tex->GetHeight();
				atlasImage.Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, atlasImageWidth, atlasImageHeight, 1, 1);
				isMade = true;
			}
		}

		hr = CopyRectangle(
			*tex->GetScratchImage(),
			Rect(0, 0, tex->GetWidth(), tex->GetHeight()),
			*atlasImage.GetImages(),
			TEX_FILTER_DEFAULT,
			i * (tex->GetWidth()),
			0
		);

		//tex->CreateSRV(&atlasImage);
	}

	atlasTex->InitScratImage(atlasImageWidth, atlasImageHeight);

	CopyRectangle(
		*atlasImage.GetImages(),
		Rect(0, 0, atlasImage.GetMetadata().width, atlasImage.GetMetadata().height),
		*atlasTex->GetScratchImage(),
		TEX_FILTER_DEFAULT,
		0, 0
	);

	atlasTex->CreateSRV();

	CResourceMgr::GetInst()->Insert(L"atlas_" + spriteName, atlasTex);
}