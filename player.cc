#include "player.h"
using namespace std;

Player::Player(): downloadedDataCount{0}, downloadedVirusCount{0} {}

Status Player::checkStatus() {
    if (downloadedDataCount >= 4) return Status::Win;
    else if (downloadedVirusCount >= 4) return Status::Lose;
    else return Status::InPlay;
}
