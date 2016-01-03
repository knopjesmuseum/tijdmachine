# tijdmachine

## 14 februari 2006
- begin project?

## 2 oktober 2009
- doorontwikkeling op de Vita Nova


## 3 januari 2016 - Tijdmachine weer tot leven brengen:
- externe monitor + keyboard aansluiten
- linux start niet op:
- error:no such device: xxxxx-xxxxx-xxxxx-xxxxx
- Entering rescue mode....
- grub rescue>
- USB stick waarvan ie zou moeten booten bekeken op m’n mac. Er staat wel een linux OS op.
- naar BIOS
  - Boot > 1st Boot Device: SATA: 3M-SAMSUNG HD
  - Boot > Hard Disk Drives >
  - 1st Drive SATA:3M-SAMSUNG HD
  - 2nd Drive: USB:Imation Nano P
  - Deze twee omgewisseld. Save. Exit. Reboot. Nu zegt ie GRUB loading Welcome to GRUB. Vervolgens het GNU GRUB Menu met CrunchBang Linux.
- Lampje van USB Stick knippert. Hij lijkt bezig te zijn Linux te starten maar het scherm blijft zwart
- Na lang wachten op een zwart scherm maar op Enter gedrukt en op eens ging ie verder. Dat kan ook toeval zijn geweest
- Nu inloggen met Username en Password. Wat was dat ook al weer: knater, knopjesmuseum, spullenmannen? Paar combinaties geprobeerd. Geen resultaat.
- USB stick met OS in m’n laptop gestopt en /etc/passwd bekeken. Username is iig spullenmannen. Na lang denken wist Diana het opeens: n******.
- PS2 muis aansluiten. Werkt niet meteen. Logout / Login helpt niet. Rebooten dan maar (jammer want dat duurt wel een paar minuten). Muis werkt nog steeds niet. Andere muis dan maar. USB muis. Dat werkt.
- SATA schijf met de data lijkt niet gemount.
- GParted starten.
- Schijf is wel zichtbaar in dev als /dev/sda1 Hij zou gemount moeten zijn op /media/usb0. Hij geeft wel een warning (rood uitroepteken) met de melding: 'Unable to detect file system' met wat mogelijke oorzaken.
- Vervolgens vanuit GParted wel via context menu schijf gemount als /media/usb0. Dat lukt. Vervolgens laat ‘ls /media/usb0/‘ netjes het bestand ‘zaagsel.rgb' zien. Het bestand is 257GB.
- Er lijkt geen sourcecode of executable op het systeem te staan van de tijdmachine.
- In een mail van 14-sept-2009 vind ik twee stukjes source van Harmen. makefilm.cpp en playfilm.cpp die gebruik maken van fltk2.
- ik weet vrij zeker dat ik op mijn backupschijven thuis ook nog wel code heb.
- Harmen heeft de Shuttle met Windows XP opgezocht waar de oude openFrameworks 006 code van de tijdmachine op staat en ook de filmpjes. 75GB aan filmpjes.
- De tijdmachine executable werkt. De video bestanden worden niet gevonden want die waren verplaatst naar het bureaublad.
- De executable draait op maar 4fps. Het is niet duidelijk of die vroeger sneller heeft gewerkt.
- Bij de tijdmachine wil je staploos kunnen wisselen tussen verschillende afspeelsnelheden (maar ook ongeacht vanaf welke plek in het filmpje). Het filmpje heeft bijvoorbeeld 1 miljoen frames. Daarbinnen wil je of heel langzaam of heel snel of alles tussen in kunnen maar je wil dus ook kunnen offsetten om bijv precies synchroon te lopen met de frequentie van het lichtnet 50Hz zodanig dat je precies met de knippering van een TL-buis kunt syncen.
- Hier is een commando om de snelheid van een filmpje met `ffmpeg` te beinvloeden. Je dropt hiermee een hoop frames waardoor je filmpje lichter wordt. Als je bijv 10 verschillende snelheden volgens deze techniek rendert heb je al iets interessants. Het nadeel hierbij is dat je meer traploos kunt wisselen van snelheid (je moet naar een ander filmpje overschakelen). Een ander nadeel is dat je niet kunt offsetten. Omdat je dan per offset ook een apart filmpje moet maken omdat ffmpeg dan andere frames moet droppen:
```bash
ffmpeg -i pan-gop1.mov -q:v 0 -vcodec mpeg4 -r 16 -filter:v "setpts=0.001*PTS" pan-pts0.001.mov  # setpts=1/speed` dus 0.25 is 4x zo snel.
```
