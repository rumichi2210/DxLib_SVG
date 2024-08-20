#pragma once
#include <memory>
#include <string>

/*
MIT License

Copyright (c) 2024 rumichi <rumichi@latestal.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

namespace DxLibExtension {

	struct SVG
	{
		virtual ~SVG() = default;

		/// @brief 指定したサイズにレンダリングをした後、DxLibで描画可能な形式に変換します。
		/// @param width X方向における描画最大値
		/// @param height Y方向における描画最大値
		/// @param bgColor バックグラウンドカラー
		/// @note width,heightの内どちらかが０の時、値が指定されているサイズに合わせてスケーリングされます。\n
		/// ただしどちらも0の場合ドキュメントのDefaultサイズが指定されます
		/// @return レンダリングに成功した場合true/失敗した場合false
		virtual bool Render(std::uint32_t width = 0U, std::uint32_t height = 0U, std::uint32_t bgColor = 0x00000000) = 0;

		/// @brief デフォルトの画像サイズを取得
		/// @return width/height
		virtual std::tuple<double, double> GetDefaultSize() = 0;

		/// @brief 実際にレンダリングされたサイズを取得
		/// @return width/height
		virtual std::tuple<double, double> GetRenderSize() = 0;

		/// @brief DrawRotaGraph3F準拠の描画関数
		/// @param x 描画位置X
		/// @param y 描画位置Y
		/// @param cx 描画の始点位置Y
		/// @param cy 描画の始点位置X
		/// @param exRateX X軸の拡大値
		/// @param exRateY Y軸の拡大値
		/// @param angle 描画角度
		virtual void Draw(float x, float y, float cx = 0, float cy = 0, float exRateX = 1.0, float exRateY = 1.0, float angle = 0.0) = 0;


	};

	/// @brief SVGファイルからDxLibで描画可能なオブジェクトを作成します。
	/// @param filePath SVGファイルパス
	/// @return 作成したオブジェクト
	/// @note 描画するにはRenderを呼び出して置く必要があります。
	std::unique_ptr<SVG> LoadSvg(const std::string& filePath);

	/// @brief SVGファイルからDxLibで描画可能なオブジェクトを作成します。
	/// @param filePath SVGファイルパス
	/// @param width 最大の横のサイズ
	/// @param height 最大の縦のサイズ
	/// @param bgColor バックグラウンドカラー
	/// @return 作成した描画オブジェクト
	/// @note Renderまでをすべて処理します。
	std::unique_ptr<SVG> LoadSvg(const std::string& filePath, std::uint32_t width, std::uint32_t height, std::uint32_t bgColor = 0x00000000);
}

