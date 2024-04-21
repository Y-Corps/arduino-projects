void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud
}

void loop() {
  if (Serial.available() > 0) { // Check if data is available to read
    // Data is available, read it
    String receivedData = Serial.readStringUntil('\n'); // Read the incoming data until newline character
    Serial.println("Received data: " + receivedData); // Print the received data
  }
}