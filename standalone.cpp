//
// Created by Gavin on 02/07/2015.
//

#define STANDALONE 1

#include "dcf77.h"


void output_handler(const DCF77_Clock::time_t &decoded_time) {

    if (decoded_time.second.val!=0) return;

    std::cout << "OutTime: ";
    std::cout << (int)decoded_time.day.digit.hi << (int)decoded_time.day.digit.lo;
    std::cout << "/" << (int)decoded_time.month.digit.hi << (int)decoded_time.month.digit.lo;
    std::cout << "/20" << (int)decoded_time.year.digit.hi << (int)decoded_time.year.digit.lo << " ";

    std::cout << (int)decoded_time.hour.digit.hi << (int)decoded_time.hour.digit.lo;
    std::cout << ":" << (int)decoded_time.minute.digit.hi << (int)decoded_time.minute.digit.lo;
    std::cout << ":" << (int)decoded_time.second.digit.hi << (int)decoded_time.second.digit.lo;

    if (decoded_time.uses_summertime) std::cout << " BST";

    std::cout << std::endl;

}

int main() {

    DCF77_Clock_Controller::set_output_handler(&output_handler);
    std::ifstream infile("capture_20150804b.csv");

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