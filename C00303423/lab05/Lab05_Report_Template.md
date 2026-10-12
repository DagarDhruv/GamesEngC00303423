# Lab 05 — Report

**Name:** Dhruv Dagar

**StudentID:** C00303423


## Coverage summary

State coverage:  3 / 3
Transition coverage:  5 / 5

## Report (250-500 words max)

    1. state coverage means the test get all of the states once and transition coverage means tests uses every arrow in the diagram , we can have 100% state coverage without having the State coverage only tells me where the machine has been, not how it got there. That is why I added one test for each transition. Now I have 6 passing tests.


    2. If I wrote this in the PAUSED case of transition()
    if (e == Event::resume) return State::PAUSED; wrong, should be State::ON then resume would leave the machine stuck in PAUSED forever instead of going back to ON. The state coverage test never uses resume, so it still reaches all 3 states and passes. The bug is not found. PausedResumeGoesToOn expects State::ON but would get State::PAUSED, so it fails. Transition coverage catches the bug and state coverage does not. So 100 % state coverage on its own is not enough to trust the code, and each transition needs its own test.


## Screenshots
To be provided as:
* `screenshots/vscode.png`
* `screenshots/terminal.png`
