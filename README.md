# Pathwright
A real-time traffic routing engine for NYC, built in C++ on top of 
live OpenStreetMap road data and the TomTom Flow API. Computes the fastest 
driving route between any two streets using live traffic speeds, benchmarks 
three shortest-path algorithms head-to-head, and serves results over HTTP 
with visual route plotting.

## Status
core routing engine complete, accuracy improvements in progress.

## What It Does
- Fetches live road network data for 2000 meter radius around John Jay College from OpenStreetMap
- Constructs a weighted directed graph where every intersection is a node 
  and every road segment is a weighted edge
- Fires concurrent HTTP requests to the TomTom Flow Segment API to update 
  every edge with real-time traffic speeds
- Computes the fastest route between two streets using Dijkstra's, A*, 
  and Bellman-Ford, benchmarked side by side
- Serves routing results over a live HTTP server with visual path plotting

## How It Works

### 1. Road Network Ingestion
Pathwright sends a request to the OpenStreetMap Overpass API and pulls back 
every drivable road, intersection, and speed limit in the target area. 
No static files, no manual downloads, the graph is built fresh from live 
data on every run.

### 2. Graph Construction
The raw OSM data is parsed into a directed weighted graph:
- **Vertices**: real intersections, each with a latitude/longitude and unique OSM ID
- **Edges**: road segments connecting those intersections, tagged with 
  street name, distance (haversine), speed limit, and travel time weight
- Roads spanning multiple intersections are automatically split into 
  individual segments

### 3. Live Traffic Weights
Static speed limits alone don't reflect real driving conditions. 
Once the graph is built, Pathwright fires concurrent requests to the 
TomTom Flow Segment API using libcurl's multi interface, one request 
per edge, all in parallel and updates each edge with:
- **Current speed**: actual traffic speed right now
- **Free flow speed**: the speed under no congestion conditions
- **Road closure status**: closed roads are set to infinity weight 
  and excluded from routing

### 4. Travel Time Weighting
Each edge weight represents the estimated driving time in minutes:

This means the routing algorithms find the fastest route, not just 
the shortest one.

### 5. Routing Algorithms
Three algorithms run on the same graph and are benchmarked against each other:
Where V = # of Nodes and E = # of Edges
Given a 3km radius
| Algorithm | Time Complexity | Typical Runtime |
|---|---|---|
| Dijkstra's | O((V + E) log V) | ~10ms |
| A* | O((V + E) log V) | ~3ms |
| Bellman-Ford | O(V · E) | ~6s |

Results are served over HTTP and plotted visually with each algorithm's 
path rendered in a distinct color.

## Accuracy
Travel time estimates are validated against Google Maps. Current accuracy 
on Manhattan routes: **within 1–4 minutes**.

## How to run it on your machine
 
### Prerequisites
 
- C++ compiler with C++20 support
- `libcurl`, `nlohmann/json`, and `Crow` installed
- Node.js + npm
- A [TomTom API key](https://developer.tomtom.com/) (free tier works)
---
 
### 1. Clone the repository
 
```bash
git clone https://github.com/your-username/path-wright.git
cd path-wright
```
 
> The root of the project is the folder you land in after `cd path-wright` — it's the directory that contains `CMakeLists.txt` and the `frontend/` folder. All backend commands are run from here.
 
---
 
### 2. Set your TomTom API key
 
```bash
export TOMTOM_API_KEY=your_key_here
```
 
> On Windows (PowerShell): `$env:TOMTOM_API_KEY="your_key_here"`
 
---
 
### 3. Build and run the backend
 
From the **root of the project**:
 
```bash
mkdir build && cd build
cmake ..
make
./path-wright
```

Simply just press the run button as the backend is within a main() function
The backend server will start on `http://localhost:8000`. Keep this terminal open.
 
---
 
### 4. Run the frontend
 
Open a **new terminal**, then from the **root of the project**:
 
```bash
cd frontend
npm install
npm run dev
```
 
Open the URL Vite provides (typically `http://localhost:5173`) in your browser.
 
---
 
> **Important:** The backend must be running before interacting with the frontend. All algorithm requests are sent to `localhost:8000` — if the backend is not running, no paths will load.
 
---
 
## Tech Stack
 
**Backend**
- **C++20**
- **libcurl** — concurrent HTTP requests via `curl_multi` (Overpass API + TomTom Flow API)
- **nlohmann/json** — JSON parsing
- **Crow** — lightweight C++ HTTP server
- **OpenStreetMap Overpass API** — live road network data
- **TomTom Flow Segment API** — real-time traffic speeds and road closures
**Frontend**
- **Vite + JavaScript**
- **Leaflet.js** — interactive map rendering and polyline visualization
---
