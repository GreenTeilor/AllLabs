package by.bsuir.springmvcproject.entities;

import lombok.Getter;
import lombok.Setter;
import lombok.experimental.SuperBuilder;

@Getter
@Setter
@SuperBuilder
public class Image extends BaseEntity{
   private String imagePath;
   private int categoryId;
   private int productId;
   private boolean primary;
}
