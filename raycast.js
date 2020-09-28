const TILE_SIZE = 32;
const MAP_NUM_ROWS = 11;
const MAP_NUM_COLS = 15;

const WINDOW_WIDTH = MAP_NUM_COLS * TILE_SIZE;
const WINDOW_HEIGHT = MAP_NUM_ROWS * TILE_SIZE;

const FOV_ANGLE = 60 * (Math.PI / 180);

const WALL_STRIP_WIDTH = 5;
const NUM_RAYS = WINDOW_WIDTH / WALL_STRIP_WIDTH;

class Map {
    constructor() {
        this.grid = [
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1],
            [1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
        ];
	}
	hasWall(x, y) {
		if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
			return (true);
		var mapGridIndexX = Math.floor(x / TILE_SIZE);
		var mapGridIndexY = Math.floor(y / TILE_SIZE);
		return (this.grid[mapGridIndexY][mapGridIndexX] == 1);
	}
    render() {
        for (var i = 0; i < MAP_NUM_ROWS; i++) {
            for (var j = 0; j < MAP_NUM_COLS; j++) {
                var tileX = j * TILE_SIZE; 
                var tileY = i * TILE_SIZE;
                var tileColor = this.grid[i][j] == 1 ? "#222" : "#fff";
                stroke("#222");
                fill(tileColor);
                rect(tileX, tileY, TILE_SIZE, TILE_SIZE);
            }
        }
    }
}

class Player {
	constructor() {
		this.x = WINDOW_WIDTH / 2;
		this.y = WINDOW_HEIGHT / 2;
		this.radius = 3;
		this.turnDirection = 0; // -1 if left, +1 if right
		this.walkDirection = 0; // -1 if back, +1 if front
		this.rotationAngle = Math.PI / 2;
		this.moveSpeed = 2.0;
		this.rotationSpeed = 2 * (Math.PI / 180);
	}
	update() {
		this.rotationAngle += this.turnDirection * this.rotationSpeed;

		var moveStep = this.walkDirection * this.moveSpeed;

		var newPlayerX = this.x + moveStep * Math.cos(this.rotationAngle);
		var newPlayerY = this.y + moveStep * Math.sin(this.rotationAngle);
		if (!grid.hasWall(newPlayerX, newPlayerY)) {
			this.x = newPlayerX;
			this.y = newPlayerY;
		}
	}
	render() {
		noStroke();
		fill("red");
		circle(this.x, this.y, this.radius);
		// stroke("red");
		// line (
		// 	this.x,
		// 	this.y,
		// 	this.x + Math.cos(this.rotationAngle) * 20,
		// 	this.y + Math.sin(this.rotationAngle) * 20
		// )
	}
}

class Ray {
	constructor(rayAngle) {
		this.rayAngle = normalizeAngle(rayAngle);
		this.wallHitX = 0;
		this.wallHitY = 0;
		this.distance = 0;

		this.isRayFacingDown = this.rayAngle > 0 && this.rayAngle < Math.PI;
		this.isRayFacingUp = !this.isRayFacingDown;

		this.isRayFacingRight = this.rayAngle < 0.5 * Math.PI || this.rayAngle > 1.5 * Math.PI;
		this.isRayFacingLeft = !this.isRayFacingRight;
	}
	cast(columnId) {
		var xintercept, yintercept;
		var xstep, ystep;

		console.log("isRayFacingRight?", this.isRayFacingRight);

		//HORIZOZNTAL RAY-Grid intersection code
		yintercept = Math.floor(player.y / TILE_SIZE) * TILE_SIZE;
		yintercept += this.isRayFacingDown ? TILE_SIZE : 0;

		xintercept = player.x + (yintercept - player.y) / Math.tan(this.rayAngle);

		ystep = TILE_SIZE;
		ystep *= this.isRayFacingUp ? -1 : 1;

		xstep = TILE_SIZE / Math.tan(this.rayAngle);
		xstep *= (this.isRayFacingLeft && xstep > 0) ? -1 : 1;
		xstep *= (this.isRayFacingRight && xstep < 0) ? -1 : 1;
	}
	render() {
		stroke("rgba(0, 255, 0, 0.4)");
		line(
			player.x,
			player.y,
			player.x + Math.cos(this.rayAngle) * 30, //30 is ray's length
			player.y + Math.sin(this.rayAngle) * 30
		);
	}
}

var grid = new Map();
var player = new Player();
var rays = [];

function normalizeAngle(angle) {
	angle = angle % (2 * Math.PI);
	if (angle < 0) {
		angle += Math.PI * 2;
	}
	return (angle);
}

function keyPressed() {
	if (keyCode == UP_ARROW) {
		player.walkDirection = 1;
	} else if (keyCode == DOWN_ARROW) {
		player.walkDirection = -1;
	} else if (keyCode == RIGHT_ARROW) {
		player.turnDirection = 1;
	} else if (keyCode == LEFT_ARROW) {
		player.turnDirection = -1;
	}
}

function keyReleased() {
	if (keyCode == UP_ARROW) {
		player.walkDirection = 0;
	} else if (keyCode == DOWN_ARROW) {
		player.walkDirection = 0;
	} else if (keyCode == RIGHT_ARROW) {
		player.turnDirection = 0;
	} else if (keyCode == LEFT_ARROW) {
		player.turnDirection = 0;
	}
}

function castAllRays() {
	var columnId = 0;

	//start first ray subtracting half of the FOV
	var rayAngle = player.rotationAngle - (FOV_ANGLE / 2);

	rays = [];

	for (var i = 0; i < 1; i++) {
		var ray = new Ray(rayAngle);
		ray.cast(columnId);
		rays.push(ray);

		rayAngle += FOV_ANGLE / NUM_RAYS;

		columnId++;
	}
}

function setup() {
    createCanvas(WINDOW_WIDTH, WINDOW_HEIGHT);
}

function update() {
	player.update();
}

function draw() {
	update();
	
	grid.render();
	for (ray of rays) {
		ray.render();
	}
	player.render();

	castAllRays();
}
