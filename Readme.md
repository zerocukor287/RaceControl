# Rece Control Software
This system consist of 2 separate executables available at sites, and 2 additional test exes.
The Client is responsible to handle Race events, including kart managing, time measurement, writing the summary to a `*.csv` file.
The Server reads the `*.csv` file and calculate the best kart with its best lap.

# Build
Compatible with Visual Studio 2022. Open the `RaceControl.sln` file, select any build configuration, and hit build.

# Limitations
- The `ServerTest` only passes if the test data placed under `D:\MYLAPS_2\ServerTest\TestData\karttimes.csv`
- "Midnight" races handled wrong. If someone starts its lap before midnight and finishes afterwards, negative lap time calculated.
- Connection failed to set up.. perhaps firewall issue.
- Server cannot send back the result
- Couldn't test with multiple clients, or concurrent way