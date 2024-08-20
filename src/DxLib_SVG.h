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

		/// @brief �w�肵���T�C�Y�Ƀ����_�����O��������ADxLib�ŕ`��\�Ȍ`���ɕϊ����܂��B
		/// @param width X�����ɂ�����`��ő�l
		/// @param height Y�����ɂ�����`��ő�l
		/// @param bgColor �o�b�N�O���E���h�J���[
		/// @note width,height�̓��ǂ��炩���O�̎��A�l���w�肳��Ă���T�C�Y�ɍ��킹�ăX�P�[�����O����܂��B\n
		/// �������ǂ����0�̏ꍇ�h�L�������g��Default�T�C�Y���w�肳��܂�
		/// @return �����_�����O�ɐ��������ꍇtrue/���s�����ꍇfalse
		virtual bool Render(std::uint32_t width = 0U, std::uint32_t height = 0U, std::uint32_t bgColor = 0x00000000) = 0;

		/// @brief �f�t�H���g�̉摜�T�C�Y���擾
		/// @return width/height
		virtual std::tuple<double, double> GetDefaultSize() = 0;

		/// @brief ���ۂɃ����_�����O���ꂽ�T�C�Y���擾
		/// @return width/height
		virtual std::tuple<double, double> GetRenderSize() = 0;

		/// @brief DrawRotaGraph3F�����̕`��֐�
		/// @param x �`��ʒuX
		/// @param y �`��ʒuY
		/// @param cx �`��̎n�_�ʒuY
		/// @param cy �`��̎n�_�ʒuX
		/// @param exRateX X���̊g��l
		/// @param exRateY Y���̊g��l
		/// @param angle �`��p�x
		virtual void Draw(float x, float y, float cx = 0, float cy = 0, float exRateX = 1.0, float exRateY = 1.0, float angle = 0.0) = 0;


	};

	/// @brief SVG�t�@�C������DxLib�ŕ`��\�ȃI�u�W�F�N�g���쐬���܂��B
	/// @param filePath SVG�t�@�C���p�X
	/// @return �쐬�����I�u�W�F�N�g
	/// @note �`�悷��ɂ�Render���Ăяo���Ēu���K�v������܂��B
	std::unique_ptr<SVG> LoadSvg(const std::string& filePath);

	/// @brief SVG�t�@�C������DxLib�ŕ`��\�ȃI�u�W�F�N�g���쐬���܂��B
	/// @param filePath SVG�t�@�C���p�X
	/// @param width �ő�̉��̃T�C�Y
	/// @param height �ő�̏c�̃T�C�Y
	/// @param bgColor �o�b�N�O���E���h�J���[
	/// @return �쐬�����`��I�u�W�F�N�g
	/// @note Render�܂ł����ׂď������܂��B
	std::unique_ptr<SVG> LoadSvg(const std::string& filePath, std::uint32_t width, std::uint32_t height, std::uint32_t bgColor = 0x00000000);
}

