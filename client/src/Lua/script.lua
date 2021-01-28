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

function getInput(W_STATUS, A_STATUS, D_STATUS, S_STATUS)

  local choices = {100, 200, 300, 400, 500, 600, 700, 800}
  local index = 0
  print(A_STATUS)
  print(S_STATUS)
  print(D_STATUS)
  print(W_STATUS)
  repeat
    index = math.random(1, 8)

  until(isMovementValid(choices[index], W_STATUS, A_STATUS, D_STATUS, S_STATUS))

  return choices[index]
end
