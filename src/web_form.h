
char web_header[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";

char web_form_inicio[] = "<form method=\"post\" accept-charset=\"UTF-8\" enctype=\"text/plain\">";

char web_form_label_fin[] = "\"></div>";

char web_form_wifi_ssid[] = "<div><label for=\"wifi_ssid\">Wifi SSD:</label>\
<input type=\"text\" id=\"wifi_ssid\" name=\"wifi_ssid\"  value=\"";

char web_form_wifi_password[] = "<div><label for=\"wifi_password\">wifi Password:</label>\
<input type=\"text\" id=\"wifi_password\" name=\"wifi_password\"  value=\"";

char web_form_metaespacio_host[] = "<div><label for=\"metaespacio_host\">Metaespacio host:</label>\
<input type=\"text\" id=\"metaespacio_host\" name=\"metaespacio_host\"  value=\"";

char web_form_metaespacio_port[] = "<div><label for=\"metaespacio_port\">Metaespacio Port:</label>\
<input type=\"text\" id=\"metaespacio_port\" name=\"metaespacio_port\"  value=\"";

char web_form_metaespacio_credentials[] = "<label for=\"metaespacio_credentials\">Metaespacio Credentials:</label>\
<input type=\"text\" id=\"metaespacio_credentials\" name=\"metaespacio_credentials\"  value=\"";

char web_form_sonoff_ip[] = "<div><label for=\"sonoff_ip\">Sonoff IP:</label>\
<input type=\"text\" id=\"sonoff_ip\" name=\"sonoff_ip\"  value=\"";

char web_form_sonoff_port[] = "<div><label for=\"sonoff_port\">Sonoff Port:</label>\
<input type=\"text\" id=\"sonoff_port\" name=\"sonoff_port\"  value=\"";

char web_form_sonoff_key[] = "<div><label for=\"sonoff_key\">Sonoff Key:</label>\
<input type=\"text\" id=\"sonoff_key\" name=\"sonoff_key\"  value=\"";

char web_form_fin[] = "<div class=\"button\"><button type=\"submit\">Guardar y reiniciar</button></div></form>\r\n";

char web_enviado[] = "<H2>Informacion guardada. Reiniciando...</H2>\r\n";

char web_info_credentials[] = "<div>Credenciales tipo 'user:password' en <A href=\"https://webnet77.net/cgi-bin/helpers/base-64.pl\">base64</A></div>";

char web_css[] = "form {\
  margin: 0 auto;\
  width: 300px;\
  padding: 1em;\
  border: 1px solid #CCC;\
  border-radius: 1em;\
}\
div + div {\
  margin-top: 1em;\
}\
label {\
  display: block;\
  width: 300px;\
  text-align: left;\
}\
input, textarea {\
  font: 1em sans-serif;\
  width: 300px;\
  -moz-box-sizing: border-box;\
       box-sizing: border-box;\
  border: 1px solid #999;\
}\
input:focus, textarea:focus {\
  border-color: #000;\
}\
textarea {\
  vertical-align: top;\
  height: 5em;\
  resize: vertical;\
}\
.button {\
}\
button {\
  margin-left: .5em;\
}";


char web_html_inicio[] = "<!DOCTYPE html><html><head><title>ESP</title><meta http-equiv=\"Content-Type\" content=\"text/html; charset=\"UTF-8\"\"><style>";
char web_html_tras_css[] = "</style></head><body>";
char web_html_fin[] = "</body></html>"; 