library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity task2_tb is
    Generic(n : integer := 3);
--  Port ( );
end task2_tb;

architecture Behavioral of task2_tb is
component task2_beh
  generic(
   N : INTEGER := 3 );
  port(
   Sin : in STD_LOGIC;
   SE : in STD_LOGIC;
   CLK : in STD_LOGIC;
   RST : in STD_LOGIC;
   Dout : out STD_LOGIC_VECTOR(0 to N-1) );
 end component;
 
 component task2_struct
        generic(
            N : INTEGER := 3 );
        port(
            Sin : in STD_LOGIC;
            SE : in STD_LOGIC;
            CLK : in STD_LOGIC;
            RST : in STD_LOGIC;
            Dout : out STD_LOGIC_VECTOR(0 to N-1) );
    end component;
 
 signal Sin : STD_LOGIC := '0';
 signal SE : STD_LOGIC := '1';
 signal CLK : STD_LOGIC := '0';
 signal RST : STD_LOGIC;
 
 signal Dout_beh : STD_LOGIC_VECTOR(0 to N-1);
 signal Dout_struct : STD_LOGIC_VECTOR(0 to N-1);
 
 constant clock_period : time := 10 ns;
begin
 beh : task2_beh
 generic map (
  N => N
  )
 
 port map (
  Sin => Sin,
  SE => SE,
  CLK => CLK,
  RST => RST,
  Dout => Dout_beh
  );
  
 struct : task2_struct
 generic map (
  N => N
  )
 
 port map (
  Sin => Sin,
  SE => SE,
  CLK => CLK,
  RST => RST,
  Dout => Dout_struct
  );
 
 reset: process
 begin
  RST <= '1';
  wait for clock_period;
  RST <= '0';
  wait for clock_period * (N + 1) * 2;
 end process;
 
 CLK <= not CLK after clock_period;
 Sin <= not Sin after clock_period;
 SE <= not SE after clock_period * (N + 1) * 2;


end Behavioral;
