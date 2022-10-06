#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h> 
#include <stdlib.h>
#include <main.h>
#include <collision.h>


const char kWindowTitle[] = "LC1A_21_マキユキノリ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		if (keys[DIK_W] != 0) {
			player.possition.y -= player.velocity.y;
		}
		if (keys[DIK_A] != 0) {
			player.possition.x -= player.velocity.x;
		}
		if (keys[DIK_S] != 0) {
			player.possition.y += player.velocity.y;
		}
		if (keys[DIK_D] != 0) {
			player.possition.x += player.velocity.x;
		}

		for (int num = 0; num < 10; num++) {
			if (circle[num].isactive == 1) {
				circle[num].possition.x += circle[num].velocity.x;
				circle[num].possition.y += circle[num].velocity.y;
			}
		}

		///
		/// ↓更新処理ここから
		///
		//円
		Novice::GetMousePosition(&mausepossition.x, &mausepossition.y);
		if (Novice::IsTriggerMouse(0) != 0) {
			for (int num = 0; num < 10; num++) {
				if (circle[num].isactive == 0) {
					circle[num].possition.x = mausepossition.x;
					circle[num].possition.y = mausepossition.y;
					circle[num].width.x = 50;
					circle[num].width.y = 50;
					circle[num].velocity.x = rand() % 10 - 4;
					circle[num].velocity.y = rand() % 10 - 4;
					circle[num].isactive = 1;
					break;
				}
			}
		}

		//衝突
		for (int num = 0; num < 10; num++) {
			if (circle[num].isactive == 1) {
				float a = player.possition.x - circle[num].possition.x;
				float b = player.possition.y - circle[num].possition.y;
				float len = 0;
				if (circlecollision(player.possition.x, player.possition.y, player.width.x, circle[num].possition.x, circle[num].possition.y, circle[num].width.x) == 1) {
					len = sqrtf(a * a + b * b);
					float distance = player.width.x + circle[num].width.x - len;
					if (len > 0) {
						len = 1 / len;
						a *= len;
						b *= len;

						player.possition.x += a * (distance / 2);
						player.possition.y += b * (distance / 2);
						circle[num].possition.x -= a * (distance / 2);
						circle[num].possition.y -= b * (distance / 2);

						
					}

					
				}
				
				if (circle[num].possition.x <= 50 || circle[num].possition.x >= 1230) {
					circle[num].velocity.x *= -1;
				}
				if (circle[num].possition.y <= 50 || circle[num].possition.y >= 670) {
					circle[num].velocity.y *= -1;
				}
			}
		}

		


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawEllipse(player.possition.x, player.possition.y, 50, 50, 0.0f, RED, kFillModeSolid);
		for (int num = 0; num < 10; num++) {
			if (circle[num].isactive == 1) {
				Novice::DrawEllipse(circle[num].possition.x, circle[num].possition.y, 50, 50, 0.0f,0xFFFFFFFF, kFillModeSolid);
			}
		}
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
