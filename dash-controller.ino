#include "./src/DashController.hpp"

static const byte celPin = 4;
DashController* dashController;

void setup() {
    Serial.begin(115200);
    dashController = new DashController();
}

void loop() {
    dashController->tick();
}
