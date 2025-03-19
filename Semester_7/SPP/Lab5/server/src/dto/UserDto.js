export class UserDto {

    id;
    email;
    isActivated;

    constructor(entity) {
        this.id = entity.id;
        this.email = entity.email;
        this.isActivated = entity.isActivated;
    }
}