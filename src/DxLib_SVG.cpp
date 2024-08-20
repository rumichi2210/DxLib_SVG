#include "dxlib_svg.h"
#include "DxLib.h"

#define LUNASVG_BUILD_STATIC
#include "lunasvg.h"
#pragma comment( lib, "lunasvg.lib")

namespace DxLibExtension {
	struct SVG_ final : SVG
	{
		SVG_(const std::string& filePath) {
			const auto tmpAsyncFlag = GetUseASyncLoadFlag();
			SetUseASyncLoadFlag(FALSE);
			// ファイルを開く
			const auto FileHandle = (FileRead_open(filePath.c_str()));
			// ファイルのサイズを得る
			const auto FileSize = (FileRead_size_handle(FileHandle));
			// データ格納用のメモリ領域を確保
			const auto buff = std::make_unique<std::byte[]>(FileSize);
			// ファイルを丸ごとメモリに読み込む
			FileRead_read(buff.get(), static_cast<int>(FileSize), FileHandle);
			FileRead_close(FileHandle);
			this->document = lunasvg::Document::loadFromData(reinterpret_cast<char*>(buff.get()), FileSize);
			SetUseASyncLoadFlag(tmpAsyncFlag);
		};

		SVG_(const std::string& filePath, std::uint32_t width, std::uint32_t height, std::uint32_t bgColor) {
			Render(width, height, bgColor);
		}

		~SVG_() {
			DeleteGraph(handle);
		};

		bool Render(std::uint32_t width = 0U, std::uint32_t height = 0U, std::uint32_t bgColor = 0x00000000) override {
			if (handle != -1) { DeleteGraph(handle); }
			auto bitmap = document->renderToBitmap(width, height, bgColor);
			if (!bitmap.valid()) return false;
			bitmap.convertToRGBA();//bitmap.convert(0, 1, 2, 3, true); // convert To RGBA unpremulitied
			ARGB32* src = reinterpret_cast<ARGB32*>(bitmap.data());
			if (!src)return false;
			const auto pixelSize = bitmap.height() * bitmap.width();
			this->bitmapWidth = bitmap.width();
			this->bitmapHeight = bitmap.height();
			auto data = std::make_unique<ARGB32[]>(pixelSize);
			std::memcpy(data.get(), src, bitmap.height() * bitmap.stride());

			BASEIMAGE BaseImage;
			// BASEIMAGE 構造体を０で初期化
			memset(&BaseImage, 0, sizeof(BASEIMAGE));
			CreateARGBF32ColorBaseImage(bitmap.width(), bitmap.height(), &BaseImage);

			//auto pixels = std::make_unique<ARGBF32[]>(pixelSize);

			ARGBF32* pixels = reinterpret_cast<ARGBF32*>(BaseImage.GraphData);
			for (uint32_t i = 0; i < pixelSize; ++i) {
				pixels[i] = ConvertARGB32ToARGBF32(data[i]);
			}

			//BaseImage.GraphData = pixels.get();
			this->handle = CreateGraphFromBaseImage(&BaseImage);
			ReleaseBaseImage(&BaseImage);
			return true;
		};

		std::tuple<double, double> GetDefaultSize() override { return std::make_tuple(this->document->width(), this->document->height()); }

		std::tuple<double, double> GetRenderSize() override { return std::make_tuple(this->bitmapWidth, this->bitmapHeight); }

		void Draw(float x, float y, float cx, float cy, float exRateX = 1.0, float exRateY = 1.0, float angle = 0.0) override {
			DrawRotaGraphFast3F(x, y, cx, cy, exRateX, exRateY, angle, this->handle, true);
		}
	private:
		std::unique_ptr<lunasvg::Document> document;
		int handle = -1;

		std::uint32_t bitmapWidth = -1;
		std::uint32_t bitmapHeight = -1;

		struct ARGB32 {
			uint8_t red;
			uint8_t green;
			uint8_t blue;
			uint8_t alpha;
		};

		struct ARGBF32 {
			float red;    // 赤チャンネル (R)
			float green;  // 緑チャンネル (G)
			float blue;   // 青チャンネル (B)
			float alpha;  // アルファチャンネル (A)
		};

		ARGBF32 ConvertARGB32ToARGBF32(const ARGB32& color) {
			ARGBF32 result;

			if (color.alpha == 0) {
				result.alpha = 0.0f;
				result.red = 0.0f;
				result.green = 0.0f;
				result.blue = 0.0f;
			}
			else {
				result.alpha = static_cast<float>(color.alpha) / 255.0f;
				result.red = static_cast<float>(color.red) / 255.0f;
				result.green = static_cast<float>(color.green) / 255.0f;
				result.blue = static_cast<float>(color.blue) / 255.0f;
			}
			return result;
		}

	};

	std::unique_ptr<SVG> LoadSvg(const std::string& filePath) {
		return std::make_unique<SVG_>(filePath);
	}

	std::unique_ptr<SVG> LoadSvg(const std::string& filePath, std::uint32_t width, std::uint32_t height, std::uint32_t bgColor) {
		return std::make_unique<SVG_>(filePath, width, height, bgColor);
	}

}