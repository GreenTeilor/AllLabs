library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

use IEEE.NUMERIC_STD.ALL;

entity task1_sync_tb is
    Generic(n : integer := 4);
--  Port ( );
end task1_sync_tb;

architecture Behavioral of task1_sync_tb is
component task1_sin_struct is
        generic (n: integer := 4);
        port (
            Din : in std_logic_vector(n-1 downto 0);
            EN: in std_logic;         
            CLK : in std_logic;
            Dout: out std_logic_vector(n-1 downto 0)
            );
    end component;
    
    component task1_sin_beh is
        generic (n: integer := 4);
        port (
            Din : in std_logic_vector(n-1 downto 0);
            EN: in std_logic;                           
            CLK : in std_logic;
            Dout: out std_logic_vector(n-1 downto 0)
            );
    end component;
 
 signal Din : STD_LOGIC_VECTOR(n-1 downto 0) := (others => '0');
 signal EN : STD_LOGIC := '1';
 signal CLK : std_logic := '0';
 
 signal Dout_beh : STD_LOGIC_VECTOR(n-1 downto 0);
 signal Dout_struct : STD_LOGIC_VECTOR(n-1 downto 0);
 
 constant register_size : integer := 4;
 constant clock_period : time := 10 ns;
begin
 
 beh : task1_sin_beh
 generic map (n => register_size)
 
 port map (
  Din => Din,
  EN => EN,  
  CLK => CLK,
  Dout => Dout_beh
  ); 
 
 struct : task1_sin_struct
 generic map (n => register_size)
 
 port map (
  Din => Din,
  EN => EN,     
  CLK => CLK,
  Dout => Dout_struct
  );

 CLK <= not CLK after clock_period; 
Din <= std_logic_vector(unsigned(Din) + 1) after clock_period * 2;
 
 enable: process
 begin
  EN <= '1';
  wait for clock_period;
  EN <= '0';
  wait for clock_period * 4;
 end process;

end Behavioral;
