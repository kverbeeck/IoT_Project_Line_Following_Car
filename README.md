# IoT_Project_Self_Driving_Car

Beschrijving: Mercedes benz wil zijn museum in Stuttgart automatiseren. Hiervoor willen ze een systeem, dat ervoor zorgt dat een bezoeker kan plaatsnemen in een zelfrijdende wagen. De bezoeker kan in het begin van de rondleiding gaan zitten in één van deze wagentjes en zal de hele toer van het museum doen. Op het einde van de toer stapt de bezoeker uit. Nadien rijd de wagen door naar het begin van de toer zodat een nieuwe bezoeker kan instappen. De route dat de wagentjes moeten volgen wordt vastgelegd met een witte tape op de vloer, dit maakt het mogelijk om de rondleiding aan te passen als er nieuwe stukken worden toegevoegd. Bij elk stuk zal op de route een witte dwarslijn worden geplaatst, hierdoor weet het wagentje daar een museum stuk tentoon wordt gesteld en dat het even moet stoppen. Als de bestuurder verder wil zal deze op een drukknop in het wagentje kunnen drukken waarna het wagentje doorrijdt naar het volgende item. Om opstopping te vermijden zal het wagentje automatisch na 5 minuten verder rijden. Optioneel willen ze de wagentjes ook vanop afstand bedienen, hiervoor zouden ze met een app de functie van de drukknop kunnen overnemen. Het is natuurlijk ook belangrijk dat de wagentjes niet botsen, hiervoor zal er tussen de wagentjes steeds een minimum afstand van 1,5m voorzien worden (Corona maatregel). Als een wagentje merkt dat het te dicht bij het voorgaande wagentje komt dient dit te stoppen en pas verder te rijden indien het voorgaande wagentje ook verder rijd. De wagentjes worden ook voorzien van led signalisatie. Met deze signalisatie kan het personeel in de controlekamer op camera’s zien als er zich een problemen voordoet. Een groene led zal branden indien er geen problemen zijn, een rode led zal branden indien het wagentje de lijn kwijt is. 

Vereisten:

De robot kan autonoom een parcour volgen dat wordt aangeduid d.m.v. een witte lijn.
De robot dient te stoppen bij een witte dwarslijn en kan verder rijden als: o Debestuurderopdedoorrijdknopduwt o Het wagentje 5 minuten stil staat. o Optioneel: als het controle centrum het wagentje activeert met de app.

De wagentjes mogen niet botsen o Indien er en wagentje stil staat zullen de achterliggende wagentjes afstand houden en pas doorrijden als het wagentje voor hen doorrijd.
Indien er problemen voordoen met een wagentje zal dit noodgedwongen stoppen en dit doorgeven aan het controle centrum d.m.v. led signalisatie op het wagentje 

Signalisatie bij problemen 
▪ Groene led: Geen problemen 
▪ Oranje led: obstakel (wagentje of andere) 
▪ Rode led: Lijn kwijt 

Wat verwacht Mercedes-Benz:
o Een beknopte beschrijving van de gebruikte hardware 
o Bestanden om de behuizing te produceren 
o Elektronicacomponenten o Schema’senPCB
o Gedocumenteerde code
o Beknopte beschrijving hoe ze deze wagentjes zelf kunnen produceren 
o Tutorial 

Dit alles zal hen worden aangereikt d.m.v. een GitHub pagina. Opvolging: Mercedes-Benz wil de wagentjes na 7 weken in productie nemen, hiervoor zullen er 3 beoordelingen plaat vinden. 

o Op 3 weken tijd dient het wagentje te rijden en basis functionaliteit te hebben (lijn volgen). 
o Na 5 weken willen ze zeker zijn dat de wagentjes over de correcte functies beschikt, Lijn volgen
Stoppen en doorrijden bij dwarslijn - Signalisatie 
o Na 7 weken zal er een werkend prototype getoond worden. Dit prototype zal getest worden op functionaliteit en snelheid. Het prototype mag geen losse componenten bevatten, het gebruik van een breadboard is dus niet toegelaten. Op dit moment dient ook alle documentatie te worden voorzien.
