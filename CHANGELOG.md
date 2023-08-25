# Changelog

## [0.4.3] - 2023-08-25
### Fixed
- Issue with GDAL on Ubuntu 20.04

## [0.4.2]  - 2023-07-12
### Fixed
- Problematic compilation in debug mode

## [0.4.1]  - 2023-06-05
### Fixed
- STL export bugfix

## [0.4.0] - 2023-05-03
### Added
- (breaking) Support for many polygon formats (through GDAL)
- Optional flag that enforces buildings and terrain intersection
### Changed
- Updated LAStools to v2.0.2
- Minor bugfixes

## [0.3.0] - 2023-01-18
### Added
- Building surface refinement
- Sharper boundaries of flattened polygons
- Minimum building height as an argument
### Fixed
- Bad reconstruction of buildings with low height
- Minor bugfixes

## [0.2.0] - 2022-10-07
### Added
- Point cloud preparation tool city4cfd_pcprep
### Changed
- (breaking) Terrain smoothing overhaul
### Removed
- Previous point cloud preparation script

## [0.1.2] - 2022-09-13
### Changed
- Bad triangles handling

## [0.1.1] - 2022-09-02
### Fixed
- Bad triangles at surface edges
- Polygons close to the boundary are defined as 'out of bounds'

## [0.1.0] - 2022-08-14 
First release