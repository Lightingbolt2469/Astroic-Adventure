function love.load() -- It loads ALL of the variables, booleans, strings, and object arrays required to run the game
    -- Player
    Player = {}
    Player.x = 364
    Player.y = 500
    Player.speed = 250
    Player.sprite = love.graphics.newImage("Sprites/ufo.png")
    Player.width = 90
    Player.height = 90
    -- Asteroid
    Asteroid = {}
    Asteroid.x = love.math.random(0, 672)
    Asteroid.y = 0
    Asteroid.speed = love.math.random(55, 160)
    Asteroid.sprite = love.graphics.newImage("Sprites/meteorite.png")
    Asteroid.height = 128
    Asteroid.width = 128
    -- Asteroid 2
    Asteroid2 = {}
    Asteroid2.x = love.math.random(55, 672)
    Asteroid2.y = 0
    Asteroid2.speed = love.math.random(0, 160)
    Asteroid2.sprite = love.graphics.newImage("Sprites/meteorite.png")
    Asteroid2.height = 128
    Asteroid2.width = 128
    -- Asteroid 3
    Asteroid3 = {}
    Asteroid3.x = love.math.random(55, 672)
    Asteroid3.y = 0
    Asteroid3.speed = love.math.random(0, 160)
    Asteroid3.sprite = love.graphics.newImage("Sprites/meteorite.png")
    Asteroid3.height = 128
    Asteroid3.width = 128
    -- Lazer
    Lazer = {}
    Lazer.x = Player.x + 40
    Lazer.y = Player.y
    Lazer.speed = 600
    Lazer.sprite = love.graphics.newImage("Sprites/lazer.png")
    Lazer.active = false
    Lazer.width = 11
    Lazer.height = 72
    -- Background
    Background = love.graphics.newImage("Sprites/Background.png")
    -- Score
    Score = 0
    -- Lives
    Lives = 5
    -- Lost or Won
    Lost_or_Won = 1
end

-- If space is pressed once it makes Lazer.active true, hence shooting the lazer
function love.keypressed(key)
    if key == "space" then
        Lazer.x = Player.x + 40
        Lazer.y = Player.y
        Lazer.active = true
    end
end

-- This function checks if any colision happens
function isColliding(a, b)
    return a.x < b.x + b.width and
        b.x < a.x + a.width and
        a.y < b.y + b.height and
        b.y < a.y + a.height
end

-- Handles a single hit  and removes a life
function hitPlayer()
    Lives = Lives - 1
end

function love.update(dt) -- This updates the stuff in love.load like for example the player coordinates are updated on a key press
    if Lost_or_Won == 1 then
        -- If Lazer.active is false or space is not pressed yet, it makes Lazer.x and Lazer.y the position of the player
        if Lazer.active == false then
            Lazer.x = Player.x + 40
            Lazer.y = Player.y
        end
        -- Asteroid motion, colision, randomness, and speed
        Asteroid.y = Asteroid.y + Asteroid.speed * dt
        if Asteroid.y >= 600 then
            Asteroid.y = 0
            Asteroid.x = love.math.random(0, 672)
            Asteroid.speed = love.math.random(70, 160)
            Score = Score - 1
        end
        Asteroid2.y = Asteroid2.y + Asteroid2.speed * dt
        if Asteroid2.y >= 600 then
            Asteroid2.x = love.math.random(0, 672)
            Asteroid2.y = 0
            Asteroid2.speed = love.math.random(70, 160)
            Score = Score - 1
        end
        Asteroid3.y = Asteroid3.y + Asteroid3.speed * dt
        if Asteroid3.y >= 600 then
            Asteroid3.x = love.math.random(0, 672)
            Asteroid3.y = 0
            Asteroid3.speed = love.math.random(70, 160)
            Score = Score - 1
        end
        -- Lazer motion and colision
        if Lazer.active then
            Lazer.y = Lazer.y - Lazer.speed * dt
            if Lazer.y <= 0 then
                Lazer.active = false
                Lazer.y = Player.y
            end
        end
        if Lazer.active == false or Lazer.active == true then
            if isColliding(Lazer, Asteroid) then
                Score = Score + 1
                Asteroid.y = 0
                Asteroid.speed = love.math.random(70, 160)
                Asteroid.x = love.math.random(0, 672)
                Lazer.active = false
            end
            if isColliding(Lazer, Asteroid3) then
                Score = Score + 1
                Asteroid3.y = 0
                Asteroid3.speed = love.math.random(70, 160)
                Asteroid3.x = love.math.random(0, 672)
                Lazer.active = false
            end
            if isColliding(Lazer, Asteroid2) then
                Score = Score + 1
                Asteroid2.y = 0
                Asteroid2.speed = love.math.random(70, 160)
                Asteroid2.x = love.math.random(0, 672)
                Lazer.active = false
            end
            if isColliding(Player, Asteroid2) then
                hitPlayer()
                Asteroid2.y = 0
                Asteroid2.speed = love.math.random(70, 160)
                Asteroid2.x = love.math.random(0, 672)
                Lazer.active = false
            end
            if isColliding(Player, Asteroid3) then
                hitPlayer()
                Asteroid3.y = 0
                Asteroid3.speed = love.math.random(70, 160)
                Asteroid3.x = love.math.random(0, 672)
            end
            if isColliding(Player, Asteroid) then
                hitPlayer()
                Asteroid.y = 0
                Asteroid.speed = love.math.random(70, 160)
                Asteroid.x = love.math.random(0, 672)
            end
        end
        if Lives <= 0 or Score < 0 then
            Lost_or_Won = 0
        end
        if Score == 100 then
            Lost_or_Won = 2
        end
        -- WASD control / Arrow Key control
        if love.keyboard.isDown("a") then
            Player.x = Player.x - Player.speed * dt
        end
        if love.keyboard.isDown("d") then
            Player.x = Player.x + Player.speed * dt
        end
        if love.keyboard.isDown("left") then
            Player.x = Player.x - Player.speed * dt
        end
        if love.keyboard.isDown("right") then
            Player.x = Player.x + Player.speed * dt
        end
    end
end

function love.draw() -- This draws everything on the screen you see
    -- Draws the Background
    love.graphics.draw(Background, 0, 0)
    -- Draws the score
    love.graphics.print("Score : " .. Score .. "", 20, 20)
    love.graphics.print("Lives : " .. Lives .. "", 20, 50)
    -- Draws the Lazer if Lazer.active is made true by pressing space
    if Lazer.active == true then
        love.graphics.draw(Lazer.sprite, Lazer.x, Lazer.y)
    end
    -- Draws the Player
    love.graphics.draw(Player.sprite, Player.x, Player.y)
    -- Draws the Asteroids
    love.graphics.draw(Asteroid.sprite, Asteroid.x, Asteroid.y)
    love.graphics.draw(Asteroid2.sprite, Asteroid2.x, Asteroid2.y)
    love.graphics.draw(Asteroid3.sprite, Asteroid3.x, Asteroid3.y)
    -- Won or Lost message displayed
    if Lost_or_Won == 0 then
        love.graphics.print("You Lost", 400, 300)
    end
    if Lost_or_Won == 2 then
        love.graphics.print("You Won", 400, 300)
    end
end
