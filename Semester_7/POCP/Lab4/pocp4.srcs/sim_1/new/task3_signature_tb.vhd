library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity task3_signature_tb is
    Generic(N : integer := 3);
end task3_signature_tb;

architecture Behavioral of task3_signature_tb is
component task3_signature     
  generic (N : integer := 3);
  port(
   CLK: in std_logic;
   RST: in std_logic; 
   Pin: in std_logic; 
   Pout: out std_logic_vector(0 to N-1)
   );
 end component;
 signal CLK: std_logic := '0';
 signal RST: std_logic := '0'; 
 
 signal Pout: std_logic_vector(0 to N-1);
 signal Pin: std_logic := '0';
 constant clock_period: time := 10 ns;
 constant test_polynom: std_logic_vector := "1100011";
begin
      uut: task3_signature port map (CLK => CLK, RST => RST,  POut => POut,Pin => Pin);
      simulate: process
       begin 
        wait for clock_period;
        for i in test_polynom'length-1 downto 0 loop
         Pin <= test_polynom(i);     
         wait for clock_period*2;
        end loop; 
       end process;
      CLK <= not CLK after clock_period;
end Behavioral;
