#include "BluetoothA2DPSink.h"
#include "esp_avrc_api.h"

BluetoothA2DPSink a2dp_sink;

String titulo = "";
String artista = "";
String album = "";
String dadoRecebido = "";

void setup() {
  Serial.begin(115200);
  a2dp_sink.set_auto_reconnect(true, 10);
  a2dp_sink.set_avrc_metadata_callback(avrc_metadata_callback);
  a2dp_sink.start("ESP32thing");
}

void loop() {
}

void avrc_metadata_callback(uint8_t data1, const uint8_t *data2) {
  dadoRecebido = String((char *) data2);  // converte valor recebido em String
  switch (data1) {
    case esp_avrc_md_attr_mask_t::ESP_AVRC_MD_ATTR_TITLE:
      if (! dadoRecebido.equals(titulo)) {
        titulo = dadoRecebido;
        Serial.printf("Título: %s\n", titulo);
      }
      break;
    case esp_avrc_md_attr_mask_t::ESP_AVRC_MD_ATTR_ARTIST:
      if (! dadoRecebido.equals(artista)) {
        artista = dadoRecebido;
        Serial.printf("Artista: %s\n", artista);
      }
      break;
    case esp_avrc_md_attr_mask_t::ESP_AVRC_MD_ATTR_ALBUM:
      if (! dadoRecebido.equals(album)) {
        album = dadoRecebido;
        Serial.printf("Álbum: %s\n", album);
      }
      break;
  }
}
