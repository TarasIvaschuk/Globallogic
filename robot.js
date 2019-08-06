const roads = [
"Alice's House-Bob's House", "Alice's House-Cabin",
"Alice's House-Post Office", "Bob's House-Town Hall",
"Daria's House-Ernie's House", "Daria's House-Town Hall",
"Ernie's House-Grete's House", "Grete's House-Farm",
"Grete's House-Shop", "Marketplace-Farm",
"Marketplace-Post Office", "Marketplace-Shop",
"Marketplace-Town Hall", "Shop-Town Hall"
];

function buildGraph(edges) {
  let graph = Object.create(null);
  function addEdge(from, to) {
    if (graph[from] == null) {
      graph[from] = [to];
    } else {
      graph[from].push(to);
    }
  }
  for (let [from, to] of edges.map(r => r.split("-"))) {
    addEdge(from, to);
    addEdge(to, from);
  }
  return graph;
}

/* 1. we have buid a graph  */

const roadGraph = buildGraph(roads);

class VillageState {
  constructor(place, parcels) {
    this.place = place;
    this.parcels = parcels;
  }
  move(destination) {
    if (!roadGraph[this.place].includes(destination)) {
      return this;
    } else {
      let parcels = this.parcels
        .map(p => {
          if (p.place != this.place) return p;
          return { place: destination, address: p.address };
        })
        .filter(p => p.place != p.address);
      return new VillageState(destination, parcels);
    }
  }
}
/* this is the main function */

function runRobot(state, robot, memory) {
  for (let turns = 0; ; turns++) {
    if (state.parcels.length == 0) {
      console.log(`Done in ${turns} turns`);
      break;
    }
    let action = robot(state, memory);
    state = state.move(action.direction);
    memory = action.memory;
    console.log(`Moved to ${action.direction}`);
  }
}
/* this is option with random robot . Not so efficient without memory*/

var randomPick=(array)=> {
  let choice = Math.floor(Math.random() * array.length);
  return array[choice];
}
function randomRobot(state) {
  return { direction: randomPick(roadGraph[state.place]) };
}

/* this is used to create start conditions.
This generates start state */

VillageState.random = function (parcelCount = 5) {
  let parcels = [];
  for (let i = 0; i < parcelCount; i++) {
    let address = randomPick(Object.keys(roadGraph));
    let place;
    do {
      place = randomPick(Object.keys(roadGraph));
    } while (place == address);
    parcels.push({ place, address });
  }
  return new VillageState("Post Office", parcels);
};

/* this is 2 option. It is faster than random
 robot but not optimal*/

const mailRoute = [
  "Alice's House", "Cabin", "Alice's House", "Bob's House",
  "Town Hall", "Daria's House", "Ernie's House",
  "Grete's House", "Shop", "Grete's House", "Farm",
  "Marketplace", "Post Office"
];

function routeRobot(state, memory) {
  if (memory.length == 0) {
      memory = mailRoute;
  }
  return { direction: memory[0], memory: memory.slice(1) };
}

/* this is third option with smart robot.
The fastest one */

function findRoute(graph, from, to) {
  let work = [{ at: from, route: [] }];
  for (let i = 0; i < work.length; i++) {
    let { at, route } = work[i];
    for (let place of graph[at]) {
      if (place == to) return route.concat(place);
      if (!work.some(w => w.at == place)) {
        work.push({ at: place, route: route.concat(place) });
      }
    }
  }
}

function goalOrientedRobot({ place, parcels }, route) {
  if (route.length == 0) {
    let parcel = parcels[0];
    if (parcel.place != place) {
      route = findRoute(roadGraph, place, parcel.place);
    } else {
      route = findRoute(roadGraph, place, parcel.address);
    }
  }
  return { direction: route[0], memory: route.slice(1) };
}

function cleverRobot({ place, parcels }, route) {
  if (route.length == 0){
    let routes = parcels.map(parcel => {
      if (parcel.place != place) {
        return {route: findRoute(roadGraph, place, parcel.place),
                pickUp: true};
      } else {
        return {route: findRoute(roadGraph, place, parcel.address),
                pickUp: false};
      }
    });
    console.log (routes);
  }
  return  {direction: route[0], memory: route.slice(1) };
}

function compareRobots(robot1, robot2, mailRoute,randomPick) {
  let measurements=100;
  let rbt1Steps=0;
  let rbt2Steps=0;
  let memoryRbt1=[];
  let memoryRbt2=[];
  memoryRbt1=randomMemory(mailRoute,randomPick);
  memoryRbt2=randomMemory(mailRoute,randomPick);

  for (let i =0; i<measurements;i++){
    let state= VillageState.random();
    rbt1Steps += runRobotSteps(state, robot1, memoryRbt1);
    rbt2Steps += runRobotSteps(state, robot2, memoryRbt2);
  }

  let rbt1Avg = rbt1Steps / measurements;
  let rbt2Avg = rbt2Steps / measurements;
  console.log("The average of goalOrientedRobot  is " + rbt1Avg);
  console.log("The average of cleverRobot is " + rbt2Avg);
}

function runRobotSteps(state, robot, memory) {
  let turns=0;
  for (; ; turns++) {
    if (state.parcels.length == 0) {
      console.log(`Done in ${turns} turns`);
      return turns;
    }
    let action = robot(state, memory);
    state = state.move(action.direction);
    memory = action.memory;
    console.log(`Moved to ${action.direction}`);
  }
}
function randomMemory (mailRoute,randomPick) {
  let size = Math.floor(Math.random() * mailRoute.length);
  let memory=[];
  let choice;

  for (let i=0;i<size;i++){
    choice=randomPick(mailRoute);
    memory.push(choice);
  }
  return memory;
}

/* THE TEST DEMO OF PROGRAMM */
// let emptyRoute=[];
// runRobot(VillageState.random(), goalOrientedRobot, []);
// compareRobots(goalOrientedRobot, cleverRobot,mailRoute,randomPick);
// let s=shortestRoute(VillageState.random()); 
// runRobot(VillageState.random(), cleverRobot, []);
cleverRobot(VillageState.random() ,[]);