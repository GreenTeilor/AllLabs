library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity task1_asyn_beh is
    Generic(n : integer := 4);
    Port ( Din : in STD_LOGIC_VECTOR(n-1 downto 0);
           EN : in STD_LOGIC;
           Dout : out STD_LOGIC_VECTOR(n-1 downto 0));
end task1_asyn_beh;

architecture Behavioral of task1_asyn_beh is

begin
    Dout <= Din when EN = '1';
end Behavioral;
