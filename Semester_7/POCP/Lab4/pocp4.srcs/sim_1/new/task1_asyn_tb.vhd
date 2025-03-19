library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

use IEEE.NUMERIC_STD.ALL;

entity task1_asyn_tb is
    Generic(n : integer := 4);
end task1_asyn_tb;

architecture Behavioral of task1_asyn_tb is
component task1_async_struct is
        generic (n: integer := 4);
        port (
            Din : in std_logic_vector(n-1 downto 0);
            EN: in std_logic;
            Dout: out std_logic_vector(n-1 downto 0)
            );
    end component;
    
    component task1_asyn_beh is
        generic (n: integer := 4);
        port (
            Din : in std_logic_vector(n-1 downto 0);
            EN: in std_logic;
            Dout: out std_logic_vector(n-1 downto 0)
            );
    end component;
 
 signal Din : STD_LOGIC_VECTOR(n-1 downto 0) := (others => '0');
 signal EN : STD_LOGIC := '0';
 
 signal Dout_beh : STD_LOGIC_VECTOR(n-1 downto 0);
 signal Dout_struct : STD_LOGIC_VECTOR(n-1 downto 0);
 
 constant register_size : integer := 4;
 constant in_delay : time := 10 ns;
begin
 
 beh : task1_asyn_beh
 generic map (n => register_size)
 
 port map (
  Din => Din,
  EN => EN,
  Dout => Dout_beh
  ); 
 
 struct : task1_async_struct
 generic map (n => register_size)
 
 port map (
  Din => Din,
  EN => EN,
  Dout => Dout_struct
  );
 
 Din <= std_logic_vector(unsigned(Din) + 1) after in_delay;
 
 enable: process
 begin
  wait for in_delay / 3;
  EN <= '1';
  wait for in_delay / 3;
  EN <= '0';
  wait for in_delay * 4 + in_delay / 3;
 end process;

end Behavioral;
