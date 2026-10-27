[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver SFA40

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/sfa40/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der SFA40 ist ein Sensor für Formaldehyd (HCHO), der sich durch eine herausragende Genauigkeit im praktischen Einsatz auszeichnet – dies ist auf seine außergewöhnlich geringe Querempfindlichkeit gegenüber gängigen Gasen in Innenräumen zurückzuführen, wie etwa Ethanol oder Stickstoffdioxid. Der für Luftreiniger, Klimaanlagen und Geräte zur Überwachung der Innenraumluftqualität entwickelte SFA40 besticht durch seine kompakte Bauweise, einen niedrigen Stromverbrauch sowie zuverlässige Messergebnisse, selbst wenn andere flüchtige organische Verbindungen (VOCs) in der Umgebung vorhanden sind. Der Sensor eignet sich zur Erfassung niedriger Formaldehydkonzentrationen, die unter den Grenzwerten liegen, wie sie von der WHO, dem WELL Building Standard™ sowie der chinesischen nationalen Norm GB/T 18883-2022 festgelegt wurden. Dank einer fortschrittlichen Technologie gegen Austrocknung („Anti-Dry“-Technologie) weist dieser elektrochemische Sensor eine außergewöhnlich lange Lebensdauer auf. Jeder SFA40 ist ab Werk kalibriert und lässt sich durch manuelles oder automatisiertes Löten problemlos in das Endgerät integrieren. Damit ist der SFA40 eine zuverlässige, einfach zu handhabende und hochwertige Lösung zur Formaldehydmessung, die die Entwicklung kompakter Geräte mit langer Batterielaufzeit und erstklassiger Leistungsfähigkeit ermöglicht.

LibDriver SFA40 ist der von LibDriver gestartete Vollfunktionstreiber von SFA40. Es ermöglicht die Messung der Formaldehydkonzentration, der Temperatur, der Luftfeuchtigkeit, des SN-Werts und anderer Funktionen. LibDriver ist MISRA-kompatibel.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver SFA40-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver SFA40 IIC.

/test enthält den Testcode des LibDriver SFA40-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver SFA40-Beispielcode.

/doc enthält das LibDriver SFA40-Offlinedokument.

/Datenblatt enthält SFA40-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/sfa40/index.html](https://www.libdriver.com/docs/sfa40/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.