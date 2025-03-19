library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity task2_struct is
    Generic(n : integer := 4);
    Port ( Sin : in STD_LOGIC;
           SE : in STD_LOGIC;
           CLK : in STD_LOGIC;
           RST : in STD_LOGIC;
           Dout : out STD_LOGIC_VECTOR(0 to n -1));
end task2_struct;

architecture Behavioral of task2_struct is
component FDCPE
         Port (
          CLK, CLR : in STD_LOGIC;
          EN : in STD_LOGIC;
          D : in STD_LOGIC;
          Q : out STD_LOGIC);
end component;
signal outS: std_logic_vector(0 to n-1);        
begin
    D1: FDCPE port map( CLK => CLK, EN => SE, CLR => RST, D => Sin, Q => outS(0));
    reg: for i in 1 to n-1 generate
            DI: FDCPE port map ( CLK => CLK, EN => SE, CLR => RST, D => outS(i-1), Q => outS(i));
    end generate;
    Dout <= outS;
end Behavioral;
