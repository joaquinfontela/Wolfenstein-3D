
function getInput(GameState)

  local leftRight = {100, 200}
  local upDown = {300, 400}
  local index = 0
  local retVal = 0

  -- If player in sight, then shoot
  retVal = playerInSight(GameState)
  if(retVal == 1) then
    return 18
  end

  -- If facing Wall, switch to random direction
  -- La idea es dar una API así de específica? Tal vez podrías tener una primitiva getInSightObject y que te diga
  -- qué es lo que tenés en frente (no está mal, pero ojo con las apis que exponen)
  retVal = facingWall(GameState)
  if(retVal == 1) then
    index = math.random(1, 2)
    return leftRight[index]
  end

  -- Else, Go Foward
  return 300
end
