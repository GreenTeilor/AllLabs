package by.teachmeskills.springbootproject.csv;

import com.opencsv.bean.CsvBindByName;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.experimental.SuperBuilder;

import java.math.BigDecimal;

@Getter
@Setter
@SuperBuilder
@NoArgsConstructor
public class ProductCsv {
    @CsvBindByName
    private Integer id;

    @CsvBindByName
    private String name;

    @CsvBindByName
    private String description;

    @CsvBindByName
    private String imagePath;

    @CsvBindByName
    private String categoryName;

    @CsvBindByName
    private BigDecimal price;
}
