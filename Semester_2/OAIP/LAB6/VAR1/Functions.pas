unit Functions;

interface
//Types declaration
type
  mas = array[1..3,1..3] of integer;

//Constants declaration
const
  A:mas = ((5,1,7),
           (-10,-2,1),
           (0,1,2));
  B:mas = ((2,4,1),
           (3,1,0),
           (7,2,1));

  //Function calculates sum of matrices
  function addMatrix(X, Y: mas): mas;

  //Function calculates difference of matrices
  function subMatrix(X, Y: mas): mas;

  //Function calculates result of multiplication of matrix and number
  function multNum(num: integer; X: mas): mas;

  //Function calculates result of multiplication of matrices
  function multMatrix(X, Y: mas): mas;

  //Output matrix
  procedure outputMatrix(X: mas);

implementation

  //Function calculates sum of matrices
  function addMatrix(X, Y: mas): mas;

  var
    i, j: integer;
    temp1: mas;
  { X - matrix 1
    Y - matrix 2
    temp1 - result
    i - counter 1
    j - counter 2 }
  begin
    //Filling temp1 with 0
    for i := 1 to 3 do
      for j := 1 to 3 do
        temp1[i,j] := 0;

    //Calculating sum of matrices
    for i := 1 to 3 do
      for j := 1 to 3 do
        temp1[i,j] := X[i,j] + Y[i,j];

    //Return sum of matrices
    addMatrix := temp1;
  end;

  //Function calculates difference of matrices
  function subMatrix(X, Y: mas): mas;




  var
    i, j: integer;
    temp2: mas;
  { X - matrix 1
    Y - matrix 2
    temp2 - result
    i - counter 1
    j - counter 2 }
  begin
    //Filling temp2 with 0
    for i := 1 to 3 do
      for j := 1 to 3 do
        temp2[i,j] := 0;

    //Calculating difference of matrices
    for i := 1 to 3 do
      for j := 1 to 3 do
        temp2[i,j] := X[i,j] - Y[i,j];

    //Return difference of matrices
    subMatrix := temp2;
  end;

  //Function calculates result of multiplication of matrix and number
  function multNum(num: integer; X: mas): mas;
  var
    i, j: integer;
    temp3: mas;
  { X - matrix 1
    Y - matrix 2
    temp3 - result
    i - counter 1
    j - counter 2 }
  begin
    //Filling temp1 with 0
    for i := 1 to 3 do
      for j := 1 to 3 do
        temp3[i,j] := 0;

    //Calculate result of multiplication
    for i := 1 to 3 do
      for j := 1 to 3 do
        temp3[i,j] := X[i,j] * num;

    //Return result of multiplication of num and matrix
    multNum := temp3;
  end;

  //Function calculates result of multiplication of matrices
  function multMatrix(X, Y: mas): mas;
  var
    i, j, k: integer;
    temp4: mas;
  { X - matrix 1
    Y - matrix 2
    temp4 - result
    i - counter 1
    j - counter 2
    k - counter 3 }
  begin
    //Calculate result of multiplication
    for i := 1 to 3 do
      for j := 1 to 3 do
      begin
        temp4[i,j] := 0;
        for k := 1 to 3 do
          temp4[i,j] := temp4[i,j] + X[i,k] * Y[k,j];
      end;

    //Return result of multiplication of matrices
    multMatrix := temp4;
  end;

  //Output matrix
  procedure outputMatrix(X: mas);
  var
    i, j: integer;
  { X - matrix
    i - counter
    j - counter }
  begin
    //Output matrix
    for i := 1 to 3 do
    begin
      for j := 1 to 3 do
        write(X[i,j]:6);
      writeln;
      writeln;
    end;
  end;
end.
