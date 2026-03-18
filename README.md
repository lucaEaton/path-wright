# PathWright
A real-time road network graph built from live OpenStreetMap data, with shortest-path routing based on actual travel time. Built in C++ as the foundation for an adaptive traffic signal control system.

## Status
- Work in Progress (actively being developed)

## What It Does
- Pulls live road data for a given area of Manhattan from OpenStreetMap
- Builds a graph where every intersection is a node and every road segment is an edge
- Weights each road by how long it actually takes to drive it, not just how long it is
- Finds the fastest route between any two streets using Dijkstra's algorithm


## How It Works
### Getting the Data
The program sends a http request to the [OpenStreetMap Overpass API](https://overpass-api.de/) and pulls back every road, intersection, and speed limit in the queried area. No static files, no manual downloads — it fetches live every time.

### Building the Graph
Once the data comes back, it gets parsed into a graph:
- **Nodes** → real intersections, each with a latitude and longitude
- **Edges** → road segments connecting those intersections, tagged with street name, distance, and speed limit
- Each of these objects are matched to an unique ID

Roads with multiple intersections along them get automatically split into individual segments.

### Weights
Distance alone isn't a great measure of how long a route takes. A short road with a low speed limit can be slower than a longer road with a higher one. So each edge is weighted by **travel time** — `distance / speed` — meaning Dijkstra finds the fastest route, not just the shortest one.

### Path Finding
Dijkstra's algorithm runs on the graph to find the optimal path between two points, returning the estimated travel time in minutes.

## Next step
- Right now edge weights are based on static speed limits from the map data. The next step is making them dynamic, updating road speeds based on real-time congestion so the graph reflects what's actually happening on the street, not just what the speed limit says. From there, the goal is a full adaptive traffic signal systemm using congestion per intersection to adjust green light timings in real time, and re-routing traffic automatically as conditions change.

- Quality Assurance (QA)

## Tech Stack
- **C++**
- **libcurl** — HTTP requests to the Overpass API
- **nlohmann/json** — JSON parsing
- **OpenStreetMap** — road network data
