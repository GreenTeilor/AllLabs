unit unEditFunc;

interface
uses
  unTypes, Vcl.ComCtrls;
  function GetGroupIndexByText(group: string): integer;
  function GetBrandIndexByText(brand: string): integer;
  function GetConditionIndexByText(isReady: string): integer;
implementation

//Get group of appliance by text
function GetGroupIndexByText(group: string): integer;
begin
  if group = '���������' then
    GetGroupIndexByText := 0
  else
    if group = '�������' then
      GetGroupIndexByText := 1
    else
      if group = '���������' then
        GetGroupIndexByText := 2
      else
        GetGroupIndexBytext := 3;
end;

//Get group index of appliance by text
function GetBrandIndexByText(brand: string): integer;
begin
  if brand = 'samsung' then
    GetBrandIndexByText := 0
  else
    if brand = 'apple' then
      GetBrandIndexByText := 1
    else
      if brand = 'huawei' then
        GetBrandIndexByText := 2
      else
        if brand = 'LG' then
          GetBrandIndexBytext := 3
        else
          GetBrandIndexByText := 4;
end;

//Get condition index of appliance by text
function GetConditionIndexByText(isReady: string): integer;
begin
  if isReady = '�����' then
    GetConditionIndexByText := 1
  else
    GetConditionIndexByText := 0;
end;

end.
