//====================================================================================================
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//====================================================================================================
#define tB  4
#define tOK 5
#define tN  6
#define tOPEN     7
#define selenoid  9
#define buzzer    10

void tambahSJ(), hapusSJ(), menu() ;
uint8_t tambahSidikJari(), cekSidikJari(), hapussidikjari(uint8_t id);
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint jari = Adafruit_Fingerprint(&mySerial);
LiquidCrystal_I2C lcd(0x27, 16, 2);

uint8_t id = 1;
//====================================================================================================


void bunyi (int x = 1, int y = 800) {
  for (int h = 0 ; h < x; h++) {
    tone(buzzer, y);
    delay(300);
    noTone(buzzer);
  }
}

void setup() {
  pinMode(tB, INPUT_PULLUP);
  pinMode(tOK, INPUT_PULLUP);
  pinMode(tN, INPUT_PULLUP);
  pinMode(tOPEN, INPUT_PULLUP);
  pinMode(selenoid, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(selenoid, HIGH);
  Serial.begin(9600);
  lcd.begin();
  lcd.clear();
  jari.begin(57600);

}

void loop() {
  
  lcd.setCursor(0, 0);
  lcd.print("  DETEKSI JARI");
  lcd.setCursor(0, 1);
  lcd.print("    [ menu ]");

  cekSidikJari();
  if (digitalRead(tOPEN) == 0){
    digitalWrite(selenoid, LOW);
    lcd.clear();
    bunyi(1,300);bunyi(1,600);bunyi(1,800);
    lcd.print("  PINTU TERBUKA");
    delay(5000);
    bunyi(1,800);
    digitalWrite(selenoid, HIGH);
    lcd.clear();
  }

  
  if (digitalRead(tB) == 0) {
    while (digitalRead(tB) == 0) {}
    bunyi(1, 300);
  } else if (digitalRead(tOK) == 0) {
    while (digitalRead(tOK) == 0) {}
    bunyi(1, 500);
    menu();
  } else if (digitalRead(tN) == 0) {
    while (digitalRead(tN) == 0) {}
    bunyi(1, 800);
  }


}


//=====================MENU===============================================================================
void menu() {
setMenu1:

  if (digitalRead(tB) == 0) {
    while (digitalRead(tB) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto setMenu3;
  } else if (digitalRead(tOK) == 0) {
    while (digitalRead(tOK) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto settambah1;

  } else if (digitalRead(tN) == 0) {
    while (digitalRead(tN) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto setMenu2;
  }

  lcd.setCursor(0, 0);
  lcd.print("TAMBAH SIDIKJARI");
  lcd.setCursor(0, 1);
  lcd.print("<Back  OK  Next>");
  goto setMenu1;

setMenu2:
  if (digitalRead(tB) == 0) {
    while (digitalRead(tB) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto setMenu1;
  } else if (digitalRead(tOK) == 0) {
    while (digitalRead(tOK) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto sethapus1;

  } else if (digitalRead(tN) == 0) {
    while (digitalRead(tN) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto setMenu3;
  }


  lcd.setCursor(0, 0);
  lcd.print(" HAPUS SIDIKJARI");
  lcd.setCursor(0, 1);
  lcd.print("<Back  OK  Next>");
  goto setMenu2;

setMenu3:
  if (digitalRead(tB) == 0) {
    while (digitalRead(tB) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto setMenu2;
  } else if (digitalRead(tOK) == 0) {
    while (digitalRead(tOK) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto menuKELUAR;

  } else if (digitalRead(tN) == 0) {
    while (digitalRead(tN) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto setMenu1;
  }


  lcd.setCursor(0, 0);
  lcd.print("  >> KELUAR <<");
  lcd.setCursor(0, 1);
  lcd.print("<Back  OK  Next>");
  goto setMenu3;


  //----------------------------------------------------------------------------------------------

settambah1:
  id = 1;

  if (digitalRead(tB) == 0) {
    while (digitalRead(tB) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto settambahKembali;
  } else if (digitalRead(tOK) == 0) {
    while (digitalRead(tOK) == 0) {}
    bunyi(1, 400); lcd.clear();
    tambahSidikJari();

  } else if (digitalRead(tN) == 0) {
    while (digitalRead(tN) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto settambah2;
  }
  lcd.setCursor(0, 0);
  lcd.print("TAMBAHKAN JARI " + String(id));
  lcd.setCursor(0, 1);
  lcd.print("<Back  OK  Next>");
  goto settambah1;

settambah2:
  id = 2;

  if (digitalRead(tB) == 0) {
    while (digitalRead(tB) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto settambah1;
  } else if (digitalRead(tOK) == 0) {
    while (digitalRead(tOK) == 0) {}
    bunyi(1, 400); lcd.clear();
    tambahSidikJari();
  } else if (digitalRead(tN) == 0) {
    while (digitalRead(tN) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto settambah3;
  }
  lcd.setCursor(0, 0);
  lcd.print("TAMBAHKAN JARI " + String(id));
  lcd.setCursor(0, 1);
  lcd.print("<Back  OK  Next>");
  goto settambah2;

settambah3:
  id = 3;

  if (digitalRead(tB) == 0) {
    while (digitalRead(tB) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto settambah2;
  } else if (digitalRead(tOK) == 0) {
    while (digitalRead(tOK) == 0) {}
    bunyi(1, 400); lcd.clear();
    tambahSidikJari();
  } else if (digitalRead(tN) == 0) {
    while (digitalRead(tN) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto settambahKembali;
  }
  lcd.setCursor(0, 0);
  lcd.print("TAMBAHKAN JARI " + String(id));
  lcd.setCursor(0, 1);
  lcd.print("<Back  OK  Next>");
  goto settambah3;

settambahKembali:
  if (digitalRead(tB) == 0) {
    while (digitalRead(tB) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto settambah3;
  } else if (digitalRead(tOK) == 0) {
    while (digitalRead(tOK) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto setMenu1;

  } else if (digitalRead(tN) == 0) {
    while (digitalRead(tN) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto settambah1;
  }

  lcd.setCursor(0, 0);
  lcd.print("  >> KEMBALI <<");
  lcd.setCursor(0, 1);
  lcd.print("<Back  OK  Next>");
  goto settambahKembali;




  //----------------------------------------------------------------------------------------------
sethapus1:
  id = 1;

  if (digitalRead(tB) == 0) {
    while (digitalRead(tB) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto sethapusKembali;
  } else if (digitalRead(tOK) == 0) {
    while (digitalRead(tOK) == 0) {}
    bunyi(1, 400); lcd.clear();
    hapussidikjari(id);

  } else if (digitalRead(tN) == 0) {
    while (digitalRead(tN) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto sethapus2;
  }
  lcd.setCursor(0, 0);
  lcd.print("  HAPUS JARI " + String(id));
  lcd.setCursor(0, 1);
  lcd.print("<Back  OK  Next>");
  goto sethapus1;

sethapus2:
  id = 2;

  if (digitalRead(tB) == 0) {
    while (digitalRead(tB) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto sethapus1;
  } else if (digitalRead(tOK) == 0) {
    while (digitalRead(tOK) == 0) {}
    bunyi(1, 400); lcd.clear();
    hapussidikjari(id);

  } else if (digitalRead(tN) == 0) {
    while (digitalRead(tN) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto sethapus3;
  }
  lcd.setCursor(0, 0);
  lcd.print("  HAPUS JARI " + String(id));
  lcd.setCursor(0, 1);
  lcd.print("<Back  OK  Next>");
  goto sethapus2;


sethapus3:
  id = 3;

  if (digitalRead(tB) == 0) {
    while (digitalRead(tB) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto sethapus2;
  } else if (digitalRead(tOK) == 0) {
    while (digitalRead(tOK) == 0) {}
    bunyi(1, 400); lcd.clear();
    hapussidikjari(id);

  } else if (digitalRead(tN) == 0) {
    while (digitalRead(tN) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto sethapusKembali;
  }
  lcd.setCursor(0, 0);
  lcd.print("  HAPUS JARI " + String(id));
  lcd.setCursor(0, 1);
  lcd.print("<Back  OK  Next>");
  goto sethapus3;


sethapusKembali:
  if (digitalRead(tB) == 0) {
    while (digitalRead(tB) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto sethapus3;
  } else if (digitalRead(tOK) == 0) {
    while (digitalRead(tOK) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto setMenu2;

  } else if (digitalRead(tN) == 0) {
    while (digitalRead(tN) == 0) {}
    bunyi(1, 400); lcd.clear();
    goto sethapus1;
  }

  lcd.setCursor(0, 0);
  lcd.print("  >> KEMBALI <<");
  lcd.setCursor(0, 1);
  lcd.print("<Back  OK  Next>");
  goto sethapusKembali;

  //----------------------------------------------------------------------------------------------
menuKELUAR:
  lcd.clear();
  delay(100);

}


//================= FUNGSI TAMBAH JARI======================================================================================


uint8_t tambahSidikJari() {

  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  lcd.clear();
  lcd.print(" TEMPELKAN JARI");
  while (p != FINGERPRINT_OK) {
    p = jari.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        lcd.clear();
        lcd.print(" GAMBAR DIAMBIL");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.println(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        break;
    }
  }

  // OK success!

  p = jari.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      lcd.clear();
      lcd.print(" CONVERT GAMBAR");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  lcd.clear();
  Serial.println("Remove finger");
  lcd.print("   ANGKAT JARI");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = jari.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  lcd.setCursor(0, 1);
  lcd.print(" TEMPELKAN JARI");
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = jari.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        lcd.clear();
        lcd.print(" GAMBAR DISIMPAN");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        break;
    }
  }

  // OK success!

  p = jari.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);
  lcd.clear();
  lcd.print("  MENYIMPAN...");

  p = jari.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  Serial.print("ID "); Serial.println(id);
  p = jari.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
    lcd.clear();
    lcd.print(" SIDIKJARI BARU");
    lcd.setCursor(0, 1);
    lcd.print("    TERSIMPAN");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }
}


//=======================FUNGSI CEK JARI================================================================================


uint8_t cekSidikJari() {
  uint8_t p = jari.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // oke sukses

  p = jari.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }


  // OK converted!
  p = jari.fingerSearch();
  if (p == FINGERPRINT_OK) {
    
    Serial.println("Found a print match!");
    digitalWrite(selenoid, LOW);
    lcd.clear();
    bunyi(1,300);bunyi(1,600);bunyi(1,800);
    lcd.print("  PINTU TERBUKA");
    delay(5000);
    bunyi(1,800);
    digitalWrite(selenoid, HIGH);
    lcd.clear();
    
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    
    lcd.clear();
    bunyi(1,800);delay(100);bunyi(1,800);delay(100);bunyi(1,800);
    lcd.print(" KAMU SIAPA.?");
    delay(1000);
    lcd.clear();
    return p;
    
  } else {
    Serial.println("Unknown error");
    return p;
  }

  // found a match!
  Serial.print("Found ID #");
  Serial.print(jari.fingerID);

  return jari.fingerID;
}

//=======================FUNGSI HAPUS JARI================================================================================

uint8_t hapussidikjari(uint8_t id) {
  uint8_t p = -1;

  p = jari.deleteModel(id);

  if (p == FINGERPRINT_OK) {
    Serial.println("Deleted!");

    lcd.clear();
    lcd.print("  " + String(id) + "  DIHAPUS");
    delay(500);lcd.clear();
    
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not delete in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.print("Unknown error: 0x"); Serial.println(p, HEX);
    return p;
  }
}
