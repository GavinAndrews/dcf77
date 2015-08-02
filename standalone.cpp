//
// Created by Gavin on 02/07/2015.
//

#define STANDALONE 1

#include "dcf77.h"


void output_handler(const DCF77_Clock::time_t &decoded_time) {
    std::cout << "Hello";
}

int main() {

    DCF77_Clock_Controller::set_output_handler(&output_handler);
    std::ifstream infile("capture_20150628.csv");

    uint8_t a;
    std::string line;
    int i = 0;
    while (infile >> line) {
        a = atoi(line.c_str());
        for (int j = 0; j < 10; j++) {
            DCF77_Clock_Controller::process_1_kHz_tick_data(a);
        }
        i++;
        if (i == (100*309 - 0*100)) {
            // Let 6 mins data flow first
            i = 0;
        }
    }
    return 0;
}

uint8_t min(uint8_t a, uint8_t b) { return a; }
int cli() { return 0; };


int16_t TCCR2B;
int16_t TCCR2A;
int16_t OCR2A;
int16_t TIMSK0;
int TIMSK2;
uint8_t SREG;

DummySerial Serial;

uint8_t reverse(uint8_t b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}