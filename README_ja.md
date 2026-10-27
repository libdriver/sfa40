[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver SFA40

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/sfa40/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

SFA40は、エタノールや二酸化窒素といった屋内に一般的に存在するガスに対する交差感度が極めて低く、現場環境において卓越した精度を発揮するホルムアルデヒド（HCHO）センサーです。空気清浄機、エアコン、室内空気質モニター向けに開発されたSFA40は、小型かつ低消費電力であり、他の揮発性有機化合物（VOC）が存在する環境下でも信頼性の高い出力を実現します。本センサーは、WHO（世界保健機関）、WELL Building Standard™、および中国国家標準GB/T 18883-2022が定める基準値よりも低い濃度のホルムアルデヒドを検出するのに適しています。また、高度な「乾燥防止技術（anti-dry technology）」を採用しており、電気化学式センサーでありながら非常に長い製品寿命を誇ります。各SFA40は工場出荷時に校正済みであり、手作業または自動はんだ付けによって最終製品へ容易に組み込むことが可能です。このように、SFA40は信頼性が高く、使いやすく、かつ高品質なホルムアルデヒド検知ソリューションであり、長寿命なバッテリー駆動かつ高性能な小型機器の実現を可能にします。

LibDriver SFA40 は、LibDriver によって起動される SFA40 のフル機能ドライバーです。 ホルムアルデヒド濃度読み取り、温度読み取り、湿度読み取り、SN読み取りなどの機能を提供します。 LibDriver は MISRA に準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver SFA40のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver SFA40用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver SFA40ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver SFA40プログラミング例が含まれています。

/ docディレクトリには、LibDriver SFA40オフラインドキュメントが含まれています。

/ datasheetディレクトリには、SFA40データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

#### example basic

```C
#include "driver_sfa40_basic.h"

uint8_t res;
uint32_t i;

/* init */
res = sfa40_basic_init();
if (res != 0)
{
    return 1;
}

/* start */
res = sfa40_basic_start();
if (res != 0)
{
    (void)sfa40_basic_deinit();

    return 1;
}

/* wait 65s*/
sfa40_interface_debug_print("sfa40: wait 65s.\n");

/* delay 65s */
sfa40_interface_delay_ms(1000 * 65);

/* loop */
for (i = 0; i < 3; i++)
{
    sfa40_data_t data;

    /* read data */
    res = sfa40_basic_read(&data);
    if (res != 0)
    {
        (void)sfa40_basic_stop();
        (void)sfa40_basic_deinit();

        return 1;
    }

    /* print */
    sfa40_interface_debug_print("sfa40: %d/%d.\n", i + 1, 3);
    sfa40_interface_debug_print("sfa40: formaldehyde is %0.2fppb.\n", data.formaldehyde);
    sfa40_interface_debug_print("sfa40: humidity is %0.2f%%.\n", data.humidity);
    sfa40_interface_debug_print("sfa40: temperature is %0.2fC.\n", data.temperature);

    /* delay 2000 ms */
    sfa40_interface_delay_ms(2000);
}

/* deinit */
(void)sfa40_basic_stop();
(void)sfa40_basic_deinit();

return 0;
```

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/sfa40/index.html](https://www.libdriver.com/docs/sfa40/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。