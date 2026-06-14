#include "TestUtils.h"

TEST(ClienteTest, ValidaNifEIgualdade) {
    Cliente cliente("Ana Paciente", "123456789", "912345678");
    Cliente mesmoNif("Outro Nome", "123456789");
    Cliente mesmoNome("Ana Paciente");

    EXPECT_EQ("123456789", cliente.getNif());
    EXPECT_TRUE(cliente == mesmoNif);
    EXPECT_TRUE(cliente == mesmoNome);

    EXPECT_THROW(Cliente invalido("An", "123456789"), std::invalid_argument);
    EXPECT_THROW(Cliente invalido("Ana Paciente", "123"), std::invalid_argument);
}
