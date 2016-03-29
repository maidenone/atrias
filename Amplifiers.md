# Introduction #

This page details the status of each amplifier, including its location, state of functionality, repairs and tests performed, and any other relevant information. The next section contains a matrix of basic amplifier status, and then each amplifier has a section dedicated to it containing more detailed information and history.

Each time anything is done with an amplifier, it should be added to this page and appended with the date and the name of the person working with it. The goal is to eventually have a detailed history of each amplifier and be able to tell at a glance how many functional amplifiers are available, which amplifiers are in each robot, etc.

Each amplifier is labelled with a ID, starting with a letter and ending with a number. Each time an amplifier is labelled, it should be added to the list immediately to avoid more than one amplifier with the same ID. Currently all IDs are prefixed with the letter A.

[amplifier datasheet](http://www.a-m-c.com/download/datasheet/dzralte-060l080.pdf)

**Please change both the amplifier matrix AND the appropriate amplifier details section when making changes!**


# Amplifier Matrix #
|ID |Location                    |Status|
|:--|:---------------------------|:-----|
|A1 |Amplifier tray, DRL         |Bad   |
|A2 |Amplifier tray, DRL         |Good  |
|A3 |Amplifier tray, DRL         |Good  |
|A4 |Amplifier tray, DRL         |Bad   |
|A5 |Amplifier tray, DRL         |Good  |
|A6 |Amplifier tray, DRL         |Good  |
|A7 |Amplifier tray, DRL         |Good  |
|A8 |Amplifier tray, DRL         |Bad   |
|A9 |Amplifier tray, DRL         |Bad   |
|A10|Amplifier tray, DRL         |Bad   |
|A11|Amplifier tray, DRL         |Good  |
|A12|Amplifier tray, DRL         |Bad   |
|A13|Amplifier tray, DRL         |Bad   |
|A14|Amplifier tray, DRL         |Needs repair|

Amplifiers needing testing: None

Amplifiers needing repair: A14

# Amplifier Details #
## A1 ##
|Model         |AMC DZRALTE-060l080|
|:-------------|:------------------|
|Current Status|Bad                |
|Location      |Amplifier tray, DRL|
|Last Change   |8/21/2013          |
|Changed By    |Soo-Hyun Yoo       |

8/19/2013 - Michael Anderson:
Amplifier labelled as A1. Amplifier was previously modified for dual-amplifier testing, but has had traces reconnected to restore previous functionality. Amplifier status unknown, ready for testing.

8/21/2013 - Soo-Hyun Yoo:
Cannot communicate with amplifier through either Medulla/Menial or directly.

## A2 ##
|Model         |AMC DZRALTE-060l080|
|:-------------|:------------------|
|Current Status|Good               |
|Location      |Amplifier tray, DRL|
|Last Change   |8/23/2013          |
|Changed By    |Soo-Hyun Yoo       |

8/19/2013 - Michael Anderson:
Amplifier labelled as A2. Amplifier was previously modified for dual-amplifier testing, and some traces have been reconnected, but not all of them. Needs other traces reconnected before testing.

8/23/2013 - Soo-Hyun Yoo:
All traces reconnected. Needs testing.

8/26/2013 - Michael Anderson:
Amplifier tested at +/- 1 A. Appears fully functional.

## A3 ##
|Model         |AMC DZRALTE-060l080|
|:-------------|:------------------|
|Current Status|Good               |
|Location      |Amplifier tray, DRL|
|Last Change   |8/26/2013          |
|Changed By    |Michael Anderson   |

8/19/2013 - Michael Anderson:
Amplifier labelled as A3. Amplifier is missing heatsink, but appears otherwise complete. I believe that this might have been the benchmark amplifier for the Thunderbox project. Needs heatsink reattached before testing.

8/22/2013 - Soo-Hyun Yoo:
Heatsink reattached. Needs testing.

8/26/2013 - Michael Anderson:
Amplifier tested at +/- 1 A. Appears fully functional.

## A4 ##
|Model         |AMC DZRALTE-060l080|
|:-------------|:------------------|
|Current Status|Bad                |
|Location      |Amplifier tray, DRL|
|Last Change   |8/21/2013          |
|Changed By    |Soo-Hyun Yoo       |

8/19/2013 - Michael Anderson:
Amplifier labelled as A4. Amplifier appears complete and unmodified. Needs testing.

8/21/2013 - Soo-Hyun Yoo:
Can communicate, but does not drive motor. Motor buzzes when amplifier is enabled (probably just power).

## A5 ##
|Model         |AMC DZRALTE-060l080|
|:-------------|:------------------|
|Current Status|Good               |
|Location      |Amplifier tray, DRL|
|Last Change   |8/26/2013          |
|Changed By    |Michael Anderson   |

8/19/2013 - Michael Anderson:
Amplifier labelled as A5. Amplifier was previously used as a master amplifier for dual-amplifier testing, and has an extra wire that should be removed. Additionally, one of the gate driver capacitors is damaged and needs replacement before testing.

8/26/2013 - Michael Anderson:
Removed extra wire and replaced gate drive capacitor, then tested at +/- 1 A. Appears fully functional.

## A6 ##
|Model         |AMC DZRALTE-060l080|
|:-------------|:------------------|
|Current Status|Good               |
|Location      |Amplifier tray, DRL|
|Last Change   |8/21/2013          |
|Changed By    |Soo-Hyun Yoo       |

8/19/2013 - Michael Anderson:
Amplifier labelled as A6. Amplifier was previously used as a master for dual-amplifier testing, but appears to be complete. Needs testing.

8/21/2013 - Soo-Hyun Yoo:
Amplifier tested at +/- 1 A. Appears fully functional.

## A7 ##
|Model         |AMC DZRALTE-060l080|
|:-------------|:------------------|
|Current Status|Good               |
|Location      |Amplifier tray, DRL|
|Last Change   |8/21/2013          |
|Changed By    |Soo-Hyun Yoo       |

8/19/2013 - Michael Anderson:
Amplifier labelled as A7. Amplifier was previously used as a master for dual-amplifier testing, but appears to be complete. Needs testing.

8/21/2013 - Soo-Hyun Yoo:
Amplifier tested at +/- 1 A. Appears fully functional.

## A8 ##
|Model         |AMC DZRALTE-060l080|
|:-------------|:------------------|
|Current Status|Bad                |
|Location      |Amplifier tray, DRL|
|Last Change   |8/26/2013          |
|Changed By    |Michael Anderson   |

8/19/2013 - Michael Anderson:
Amplifier labelled as A8. Amplifier was previously modified for dual-amplifier testing, and traces that were cut need to be reconnected before testing. Additionally, a gate driver capacitor is damaged and may require replacement.

8/23/2013 - Soo-Hyun Yoo:
All traces reconnected. Needs testing.

8/26/2012 - Michael Anderson:
Capacitor on amplifier still damaged. Draws a lot of current on the 5 volt rail and makes a faint buzzing noise. I was not able to connect to the amplifier via DriveWare. It is possible that these issues are due to the broken capacitor. Requires additional repair.

8/26/2012 - Michael Anderson:
Repaired capacitor. Issue with current draw and buzzing remains. Declaring this amplifier as bad.

## A9 ##
|Model         |AMC DZRALTE-060l080|
|:-------------|:------------------|
|Current Status|Bad                |
|Location      |Amplifier tray, DRL|
|Last Change   |8/26/2013          |
|Changed By    |Michael Anderson   |

8/19/2013 - Michael Anderson:
Amplifier labelled as A9. Amplifier was previously modified for dual-amplifier testing, and traces that were cut need to be reconnected before testing.

8/26/2013 - Michael Anderson:
Reconnected all cut traces. Successfully connected via DriveWare, but amplifier does not drive motor at all.

## A10 ##
|Model         |AMC DZRALTE-060l080|
|:-------------|:------------------|
|Current Status|Bad                |
|Location      |Amplifier tray, DRL|
|Last Change   |8/26/2013          |
|Changed By    |Michael Anderson   |

8/26/2013 - Michael Anderson:
Amplifier labelled as A10. Amplifier was previously modified for dual-amplifier testing, but has had traces reconnected to restore previous functionality. Amplifier status unknown, ready for testing.

8/26/2013 - Michael Anderson:
Successfully connected via DriveWare, but amplifier does not drive motor at all.

## A11 ##
|Model         |AMC DZRALTE-060l080|
|:-------------|:------------------|
|Current Status|Good               |
|Location      |Amplifier tray, DRL|
|Last Change   |8/26/2013          |
|Changed By    |Michael Anderson   |

8/26/2013 - Michael Anderson:
Amplifier labelled as A11. Amplifier was previously used as a master for dual-amplifier testing, but appears to be complete. Needs testing.

8/26/2013 - Michael Anderson:
Amplifier tested at +/- 1 A. Appears fully functional.

## A12 ##
|Model         |AMC DZRALTE-060l080|
|:-------------|:------------------|
|Current Status|Bad                |
|Location      |Amplifier tray, DRL|
|Last Change   |8/26/2013          |
|Changed By    |Michael Anderson   |

8/26/2013 - Michael Anderson:
Amplifier labelled as A12. Amplifier was previously modified for dual-amplifier testing, but has had traces reconnected to restore previous functionality. Amplifier status unknown, ready for testing.

8/26/2013 - Michael Anderson:
Successfully connected via DriveWare, but amplifier does not drive motor at all.

## A13 ##
|Model         |AMC DZRALTE-060l080|
|:-------------|:------------------|
|Current Status|Bad                |
|Location      |Amplifier tray, DRL|
|Last Change   |8/26/2013          |
|Changed By    |Michael Anderson   |

8/26/2013 - Michael Anderson:
Amplifier labelled as A13. Amplifier was previously used as a master for dual-amplifier testing, but appears to be complete. Needs testing.

8/26/2013 - Michael Anderson:
Was able to connect to amplifier with DriveWare a single time, but DriveWare complained about errors then disconnected. All subsequent attempts to connect have failed.

## A14 ##
|Model         |AMC DZRALTE-060l080|
|:-------------|:------------------|
|Current Status|Needs repair       |
|Location      |Amplifier tray, DRL|
|Last Change   |8/26/2013          |
|Changed By    |Michael Anderson   |

8/26/2013 - Michael Anderson:
Amplifier labelled as A14. Amplifier was previously modified for dual-amplifier testing, but has had traces reconnected to restore previous functionality. Amplifier is missing heatsink. Needs heatsink reattached before testing.