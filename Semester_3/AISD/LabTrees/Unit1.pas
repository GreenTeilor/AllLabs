unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Grids, AdvObj, BaseGrid, AdvGrid, StdCtrls, Mask, AdvSpin,
  AdvGlowButton, ExtCtrls, AdvUtil;
const
  Rad=15; //Radius of tree element
  Len=40;//Distance between vertical levels
  PenColor=clBlack;
  BrushColor=clGray;
  BackColor=clWhite;
type
  Tree=^TreeEl;

  TreeEl = record
    leftNode:Tree;
    rightNode:Tree;
    value:Integer;
    thread:Boolean; //Thread of the tree
    x,y:Integer;    //Circle coordinates to draw
  end;

  TForm1 = class(TForm)
    lbl1: TLabel;
    nudElCount: TAdvSpinEdit;
    stgEls: TAdvStringGrid;
    btnBuild: TAdvGlowButton;
    imgTree: TImage;
    lbl2: TLabel;
    nudDelEl: TAdvSpinEdit;
    btnDel: TAdvGlowButton;
    lblSim: TLabel;
    lblObr: TLabel;
    lblPram: TLabel;
    procedure nudElCountChange(Sender: TObject);
    procedure btnBuildClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure btnDelClick(Sender: TObject);
  private
    { Private declarations }
  public
    rootElem:Tree;
  end;

  procedure addElem(value:Integer;var root:Tree);
  procedure drawTree(root:Tree;y,x1,x2:Integer;var bmp:TBitmap);
  function reversiveTraversial(elem:Tree):string;
  function symmetricalTraversial_andThreading(elem:Tree;var bmp:TBitmap):string;
  function directTraversial(elem:Tree):string;
  procedure dotLineTo(x0,y0,x,y:Integer;var bmp:TBitmap);
  procedure delElem(value:Integer; var Der,prevElem:Tree);
var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.nudElCountChange(Sender: TObject);
begin
  stgEls.ColCount:=nudElCount.Value + 4;
end;

//Delete element
procedure delElem(value:Integer; var Der,prevElem:Tree);
var
  prev,el,temp:Tree;
  function Find(value:Integer; var elem:Tree):Tree;
  begin
    if elem = nil then
    begin
      Result:=elem;
      Exit;
    end
    else if elem^.value = value then //Element found
      Result:=elem
    else
    begin
      prev:=elem;
      if elem^.value < value then
        Result:=Find(value,elem^.rightNode)
      else
        Result:=Find(value,elem^.leftNode)
    end;
  end;
begin
  //Search, what to delete
  prev:=prevElem;
  el:=Find(value,Der);
  if el = nil then
  begin
    MessageBoxW(0, '��������� ������� �� ������ � ������', '������', MB_OK +
      MB_ICONSTOP + MB_TOPMOST);
    Exit;
  end;
  if (el^.leftNode = nil) then //Leaf or only right subTree
  begin
    if el = prev then
      prevElem := prev^.rightNode
    else if prev^.leftNode = el then
      prev^.leftNode:=el^.rightNode
    else
      prev^.rightNode:=el^.rightNode;
    Dispose(el);
  end
  else if (el^.rightNode = nil) or (el^.thread) then //Only left subTree
  begin
    if el = prev then
      prevElem := prev^.leftNode
    else if prev^.leftNode = el then
      prev^.leftNode:=el^.leftNode
    else
      prev^.rightNode:=el^.leftNode;
    Dispose(el);
  end
  else //Both subTrees
  begin
    //The most left element of the right subTree
    temp:=el^.rightNode;
    while temp^.leftNode <> nil do
      temp:=temp^.leftNode;
    el^.value:=temp^.value;    //Remember it's value
    delElem(temp^.value,el^.rightNode,el) //Delete this element
  end;
end;

//Dotted line between 2 points
procedure dotLineTo(x0,y0,x,y:Integer; var bmp:TBitmap);
var
  x1,y1,x2,y2,i:Integer;
begin
  //Go from left to right
  if x>x0 then
  begin
    x1:=x0; y1:=y0;
    x2:=x;  y2:=y;
  end
  else
  begin
    x1:=x;  y1:=y;
    x2:=x0; y2:=y0;
  end;


  //Ox part
  i:=x1;
  while i<=x2 do
  begin
    bmp.Canvas.MoveTo(i,y1);
    bmp.Canvas.LineTo(i+5,y1);
    i:=i+10;
  end;

  //Oy part
  i:=y1;
  if y1 > y2 then
    while i>=y2 do
    begin
      bmp.Canvas.MoveTo(x2,i);
      bmp.Canvas.LineTo(x2,i-5);
      i:=i-10;
    end
  else
    while i<=y2 do
    begin
      bmp.Canvas.MoveTo(x2,i);
      bmp.Canvas.LineTo(x2,i+5);
      i:=i+10;
    end;
end;

//Reversive tree traversal
function reversiveTraversial(elem:Tree):string;
begin
  if elem = nil then
  begin
    Result:='0 ';
    Exit;
  end;

  Result:=IntToStr(elem^.value) + ' ';
  //Left subtree
  Result:=Result+reversiveTraversial(elem^.leftNode);

  Result:=Result+IntToStr(elem^.value)+ ' ';

  //Right subTree
  Result:=Result+reversiveTraversial(elem^.rightNode);


  Result:=Result + '('+IntToStr(elem^.value) + ')' + ' ';
end;

//Delete threads
procedure delThread(var elem:Tree);
begin
  if elem = nil then Exit;

  //Left subTree
  delThread(elem^.leftNode);
  if not elem^.thread then
    delThread(elem^.rightNode);
  if elem^.thread then
  begin
    elem^.thread:=False;
    elem^.rightNode:=nil;
  end;
end;

//Direct tree traversal
function directTraversial(elem:Tree):string;
begin
  if elem = nil then
  begin
    Result:='0 ';
    Exit;
  end;

  Result:=Result + '('+IntToStr(elem^.value) + ')' + ' ';

  //Left subTree
  Result:=Result+directTraversial(elem^.leftNode);
  Result:=Result+IntToStr(elem^.value)+ ' ';

  //Right subTree
  Result:=Result+directTraversial(elem^.rightNode);
  Result:=Result +IntToStr(elem^.value) + ' ';
end;

//Symmetrical tree traversal and threading (right symmetrical)
function symmetricalTraversial_andThreading(elem:Tree; var bmp:TBitmap):string;
var
  prev:Tree;
  //Recursion. Tree traversal and threading
  function threading(elem:Tree; var bmp:TBitmap):string;
  begin
    if elem = nil then
    begin
      Result:='0 ';
      Exit;
    end;

    Result:=IntToStr(elem^.value) + ' ';
    //Left subTree
    Result:=Result+threading(elem^.leftNode,bmp);
    Result:=Result + '('+IntToStr(elem^.value) + ')' + ' ';

    //Threading
    if (prev^.rightNode = nil) or (prev^.thread = true) then
    begin
      prev^.thread:=True; //Thread
      prev^.rightNode:=elem;    //Point to current
      dotLineTo(prev^.x+Rad,prev^.y,elem^.x,elem^.y+Rad,bmp);
    end
    else
      prev^.thread:=False; //If busy - not thread
    prev:=elem;

    //Right subTree
    if not elem^.thread then
    begin
      Result:=Result+threading(elem^.rightNode,bmp);
      Result:=Result+IntToStr(elem^.value)+ ' ';
    end
    else
      Result:=Result + '0 ' + IntToStr(elem^.value)+ ' ';
  end;
begin
  prev:=elem; //Initial value of previous element
  Result:=threading(elem,bmp);  //Tree traversal and threading

  //If needed - make line from head to last element

  if (prev^.rightNode = nil) then
  begin
    prev^.thread:=True; //Thread
    prev^.rightNode:=elem;    //Point to current
    dotLineTo(prev^.x+Rad,prev^.y,bmp.Width - 10,prev^.y,bmp); //Line to the right side of screen
    dotLineTo(bmp.Width-10,prev^.y,elem^.x+15,elem^.y+Rad - 15,bmp);
  end;



end;

//Add element
procedure addElem(value:Integer; var root:Tree);
begin
  if root= nil then  //Add leaf
  begin
    New(root);
    root^.value:=value;
    root^.leftNode:=nil;
    root^.rightNode:=nil;
    root^.thread:=False;
  end
  else if value<root^.value then addElem(value,root^.leftNode)     //Less - to left
  else addElem(value,root^.rightNode)                          //Bigger - to right
end;

//Tree drawing. Y - distance from top to the level;  X1,X2 - border X coordinates
procedure drawTree(root:Tree; y,x1,x2:Integer; var bmp:TBitmap);

  //Recursion to draw
  procedure drawRect(elem:Tree; y,x1,x2:Integer; var bmp:TBitmap);
  begin
    //Current element
    bmp.Canvas.Brush.Color:=BackColor;
    bmp.Height:=bmp.Height + Rad*2 + Len;
    bmp.Canvas.Ellipse((x2+x1) div 2 - Rad,y,(x2+x1) div 2 + Rad,y+Rad*2);
    bmp.Canvas.Brush.Color:=BrushColor;
    bmp.Canvas.FloodFill((x2+x1) div 2,y + Rad,PenColor,fsBorder);
    bmp.Canvas.TextOut((x2+x1) div 2 - Rad+8,y+7,IntToStr(elem^.value));
    bmp.Canvas.Brush.Color:=BackColor;
    elem^.x:=(x2+x1) div 2;
    elem^.y:=y+Rad;

    //Left subTree
    if elem^.leftNode <> nil then
    begin
      //Draw line
      bmp.Canvas.MoveTo((x1+x2) div 2,y+Rad*2);
      bmp.Canvas.LineTo(((x1+x2) div 2 + x1) div 2,y+Rad*2 + Len);
      //subTree
      drawRect(elem^.leftNode,y+Rad*2+Len,x1,(x1+x2) div 2,bmp);
    end;

    if (elem^.rightNode <> nil) and (Not elem^.thread) then
    begin
      //Draw line
      bmp.Canvas.MoveTo((x1+x2) div 2,y+Rad*2);
      bmp.Canvas.LineTo(((x1+x2) div 2 + x2) div 2,y+Rad*2 + Len);
      //subtree
      drawRect(elem^.rightNode,y+Rad*2+Len,(x1+x2) div 2,x2,bmp);
    end;
  end;
begin

  //Set height of bmp and background color
  bmp.Canvas.Brush.Color:=BackColor;
  bmp.Height:=bmp.Height + Rad*2 + Len;
  bmp.Canvas.Brush.Color:=BrushColor;

  //Rest of the tree
  drawRect(root,y+Rad*2+(Len div 2),x1,x2,bmp);
end;

procedure TForm1.btnBuildClick(Sender: TObject);
var
  i:Integer;
  elems: array of Integer;
  bmp:TBitmap;
  x:Tree;
begin
  SetLength(elems,nudElCount.Value);

  //Check validity and write
  try
    for i:= Low(elems) to High(elems) do
      elems[i]:=StrToInt(stgEls.Cells[i + 4,0]);
  except
    MessageBoxW(0, '�������� ������ ������ ����� �������� �������', '������',
      MB_OK + MB_ICONSTOP + MB_TOPMOST);
    Exit;
  end;

  //Build the tree
  rootElem:=nil;
  for i:= Low(elems) to High(elems) do
    addElem(elems[i],rootElem);

  //Draw
  bmp:=TBitmap.Create;
  with bmp do
  begin
    Canvas.Pen.Color:=PenColor;
    Canvas.Brush.Color:=BackColor;
    Width:=imgTree.Width;
  end;

  drawTree(rootElem, 0, 0,imgTree.Width,bmp);


  //Tree traversals
  lblPram.Caption:= '������ �����: ' + directTraversial(rootElem);
  lblObr.Caption:='�������� �����: '+reversiveTraversial(rootElem);
  lblSim.Caption:='������������ �����: ' + symmetricalTraversial_andThreading(rootElem,bmp);

  imgTree.Picture:=TPicture(bmp);
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  stgEls.Cells[4,0]:='4';
  stgEls.Cells[5,0]:='15';
  stgEls.Cells[6,0]:='9';
  stgEls.Cells[7,0]:='20';
  stgEls.Cells[8,0]:='14';
end;

//Delete
procedure TForm1.btnDelClick(Sender: TObject);
var
  bmp:TBitmap;
begin
  delThread(rootElem);
  delElem(nudDelEl.Value,rootElem,rootElem);

   //Draw
  bmp:=TBitmap.Create;
  with bmp do
  begin
    Canvas.Pen.Color:=PenColor;
    Canvas.Brush.Color:=BackColor;
    Width:=imgTree.Width;
  end;
  drawTree(rootElem,0,0,imgTree.Width,bmp);


  //Tree traversals
  lblPram.Caption:= '������ �����: ' + directTraversial(rootElem);
  lblObr.Caption:='�������� �����: '+reversiveTraversial(rootElem);
  lblSim.Caption:='������������ �����: ' + symmetricalTraversial_andThreading(rootElem,bmp);

  imgTree.Picture:=TPicture(bmp);
end;

end.
