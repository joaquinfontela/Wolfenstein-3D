function isMovementValid(Input, W_STATUS, A_STATUS, D_STATUS, S_STATUS)

  if(input == 100 and A_STATUS == 1) then
    return false
  elseif(input == 500 and A_STATUS == 0) then
    return false
  elseif(input == 200 and D_STATUS == 1) then
    return false
  elseif(input == 600 and D_STATUS == 0) then
    return false
  elseif(input == 300 and W_STATUS == 1) then
    return false
  elseif(input == 700 and W_STATUS == 0) then
    return false
  elseif(input == 400 and S_STATUS == 1) then
    return false
  else if(input == 800 and S_STATUS == 0) then
    return false
  else
    return true
  end
end
end



function getInput(W_STATUS, A_STATUS, D_STATUS, S_STATUS, GameState)

  local leftRight = {100, 200}
  local upDown = {300, 400}
  local index = 0
  local retVal = 0

  retVal = playerInSight(GameState)
  if(retVal == 1) then
    return 18
  end

  retVal = facingWall(GameState)
  if(retVal == 1) then
    index = math.random(1, 2)
    return leftRight[index]
  end

  index = math.random(1, 2)
  return upDown[index]
end
