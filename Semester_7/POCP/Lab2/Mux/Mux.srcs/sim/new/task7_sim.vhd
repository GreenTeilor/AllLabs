library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity task7_sim is
end task7_sim;

architecture behavioral of task7_sim is
component task7_s is
    port (
        w, x, y, z : in  STD_LOGIC;
        g : out STD_LOGIC
    );
end component;
component task7_b is
    port (
        w, x, y, z : in  STD_LOGIC;
        g : out STD_LOGIC
    );
end component;
signal w, x, y, z: STD_LOGIC;
signal g_b, g_s: STD_LOGIC;
signal error: STD_LOGIC;
signal test_vector: std_logic_vector(3 downto 0);
constant period : time := 10ns; 
begin
   TASK7S: task7_s port map (
   w => w,
   x => x,
   y => y,
   z => z,
   g => g_s
   );
   
   TASK7B: task7_b port map (
   w => w,
   x => x,
   y => y,
   z => z,
   g => g_b
   );
   
   w <= test_vector(0);
   x <= test_vector(1);
   y <= test_vector(2);
   z <= test_vector(3);
   
    sim_proc: process
      begin
        for i in 0 to 15 loop
          test_vector <= std_logic_vector(to_unsigned(i, test_vector'length));
              wait for period;
        end loop;  
      report "End of simulation" severity failure;  
      end process;
      error <= g_b xor g_s;

end Behavioral;
