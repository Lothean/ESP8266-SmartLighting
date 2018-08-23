void initWeb () {
  server.on("/", handleManager);
  server.on("/logout/", handleLogout);
  server.on("/login/", handleManagerLogin);
  server.on("/submit", handleManagerAuth);
  server.onNotFound(handleNotFound);
  const char * headerkeys[] = {"User-Agent", "Cookie"} ;
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
  //ask server to track these headers
  server.collectHeaders(headerkeys, headerkeyssize );
  server.begin();
}
void handleManagerAuth() {
  if (server.hasArg("username") && server.hasArg("pwd")) {
    for (int i = 0; i < user_count; i++) {
      if (server.arg("username") == usernames[i] &&  server.arg("pwd") == passwords[i]) {
        server.sendHeader("Location", "/");
        createCookie(i);
        server.sendHeader("Cache-Control", "no-cache");
        String cookie = "SESSION=";
        cookie += loginCookie[i];
        server.sendHeader("Set-Cookie", cookie);
        server.send(301);
        return;
      }
    }
    String content = "<head><title>Login failed!</title></head><p style='text-align: center;'><span style='color: #ff0000;'>Wrong username/password combination!</span></p><p style='text-align: center;'><a href='/login/'>Click here to go back.</a></p>";
    server.send(200, "text/html", content);
  }
  else {
    String content = "<head><title>Login failed!</title><p style='text-align: center;'><span style='color: #ff0000;'>You must enter a username/password combination.</span></p><p style='text-align: center;'><a href='/login/'>Click here to go back.</a></p>";
    server.send(200, "text/html", content);
  }
}
void createCookie (int pos) {
  loginCookie[pos] = random(0, 2147483647);
  loginCookieTicks[pos] = 0;
}
void handleNotFound () {
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plane", "");
}
void handleLogout () {
  server.sendHeader("Location", "/", true);
  if (server.hasHeader("Cookie")) {
    String askedCookie = server.header("Cookie");
    for (int i = 0; i < user_count; i++) {
      String check = "SESSION=";
      check += loginCookie[i];
      if (askedCookie == check) {
        createCookie(i);
      }
    }
  }
  server.send(302, "text/plane", "");
}
void handleManager () {
  unsigned int temp = loginCookie[0];
  if (isAuthorized()) {
    String content = "<h1>It works ! We are successfully connected :)</h1><p>Your cookie :&nbsp;";
    content += temp;
    content += "</p><p>&nbsp;</p><p>&nbsp;</p><p><a href='/logout/'>Logout</a></p>";
    server.send(200, "text/html", content);
  }

  else {
    server.sendHeader("Location", "/login/", true);
    server.send(301, "text/plane", "");
  }
}
void handleManagerLogin () {
  String content = "<head><title>ESP8266 Smart Lighting - Manager Login</title><h2 style='text-align: center;'>ESP8266 Smart Lighting - Manager Login</h2><p>&nbsp;</p><p style='text-align: center;'>Login to your manager below :</p><p style='text-align: center;'>&nbsp;</p><center><form action='/submit' method='post'><p>Username:<br /> <input name='username' type='text' /><br /> Password:<br /> <input name='pwd' type='password' /><br /><br /><button type='submit'>Log in</button></p><p>&nbsp;</p><p>&nbsp;</p><p>&nbsp;</p><p><span style='color: #ff0000;'>Your session will expire if you're inactive for too long!</span></p></form></center>";
  server.send(200, "text/html", content);
}
bool isAuthorized () {
  if (server.hasHeader("Cookie")) {
    String askedCookie = server.header("Cookie");
    for (int i = 0; i < user_count; i++) {
      String check = "SESSION=";
      check += loginCookie[i];
      if (askedCookie == check) {
        createCookie(i);
        server.sendHeader("Cache-Control", "no-cache");
        String cookie = "SESSION=";
        cookie += loginCookie[i];
        server.sendHeader("Set-Cookie", cookie);
        return true;
      }
    }
    return false;
  }
  return false;
}

