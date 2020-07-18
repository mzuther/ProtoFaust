# Change Log

*All notable changes to this project will be documented in this
file. This change log follows the conventions of
[keepachangelog.com].*


## [Unreleased]
### Added
### Changed
### Fixed



## [1.0.5] - 2020-07-18
### Added

- add custom UI handler

- add linter script and fix warnings

### Changed

- use lambda set/get functions to update controllers (thanks to
  Stéphane Letz)

- use 'alloca' which is faster than std::vector and will also work on
  Windows (thanks to Stéphane Letz)

- move some UI handling to class "ProtoFaustWidget"

- allow easier debugging of RGB LEDs (enjoy fireworks of light ...)

- re-factor code

- change selection of files formatted by astyle

### Fixed

- fix crash on opening module selection window



## [1.0.4] - 2020-07-14
### Added

- documentation: describe signal ranges

### Changed

- prevent filter from exploding

- re-factor Faust scripts and improve readability

### Fixed

- APP->engine->getSampleRate() should not be used anymore (change
  sample rate in process; thanks to Stéphane Letz)



## [1.0.3] - 2020-07-10
### Changed

- re-factor code

- change IDs of RGB LED in Faust code

### Fixed

- fix wrong scaling of three-way switches



## [1.0.2] - 2020-07-09
### Changed

- re-factor code

- beautify output of Makefile



## [1.0.1] - 2020-07-06
### Added

- add documentation, change log and code of conduct

### Changed

- improve readability of Faust code (`src/faust/rack.dsp`; thanks to
  Stéphane Letz)



## [1.0.0] - 2019-08-18
### Changed

- This is the first release.


[keepachangelog.com]:  http://keepachangelog.com/
[Unreleased]:          https://github.com/mzuther/ProtoFaust/tree/develop

[1.0.0]:  https://github.com/mzuther/ProtoFaust/commits/v1.0.0
[1.0.1]:  https://github.com/mzuther/ProtoFaust/commits/v1.0.1
[1.0.2]:  https://github.com/mzuther/ProtoFaust/commits/v1.0.2
[1.0.3]:  https://github.com/mzuther/ProtoFaust/commits/v1.0.3
[1.0.4]:  https://github.com/mzuther/ProtoFaust/commits/v1.0.4
[1.0.5]:  https://github.com/mzuther/ProtoFaust/commits/v1.0.5
