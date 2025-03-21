Предмет: СПП(Современные платформы программирования).

Лаба 1: Tracer

Необходимо реализовать измеритель времени выполнения методов.

Класс должен реализовывать следующий интерфейс:

Copy
public interface ITracer
{
    // вызывается в начале замеряемого метода
    void StartTrace();​
    
    // вызывается в конце замеряемого метода 
    void StopTrace();​
    
    // получить результаты измерений  
    TraceResult GetTraceResult();
}
Структура TraceResult на усмотрение автора.

Tracer должен собирать следующую информацию об измеряемом методе:

имя метода;

имя класса с измеряемым методом;

время выполнения метода.

Пример использования:

Copy
public class Foo
{
    private Bar _bar;
    private ITracer _tracer;

    internal Foo(ITracer tracer)
    {
        _tracer = tracer;
        _bar = new Bar(_tracer);
    }
    
    public void MyMethod()
    {
        _tracer.StartTrace();
        ...
        _bar.InnerMethod();
        ...
        _tracer.StopTrace();
    }
}

public class Bar
{
    private ITracer _tracer;

    internal Bar(ITracer tracer)
    {
        _tracer = tracer;
    }
    
    public void InnerMethod()
    {
        _tracer.StartTrace();
        ...
        _tracer.StopTrace();
    }
}
Также должно подсчитываться общее время выполнения анализируемых методов в одном потоке.

Результаты трассировки вложенных методов должны быть представлены в соответствующем месте в дереве результатов.

Результат измерений должен быть представлен в двух форматах: JSON и XML (для классов, реализующих сериализацию в данные форматы, необходимо разработать общий интерфейс).

Пример результата в JSON:

Copy
{
    "threads": [
        {
            "id": "1",
            "time": "42ms",
            "methods": [
                {
                    "name": "MyMethod",
                    "class": "Foo",
                    "time": "15ms",
                    "methods": [
                        {
                            "name": "InnerMethod",
                            "class": "Bar",
                            "time": "10ms",
                            "methods": ...    
                        }
                    ]
                },
                ...
            ]
        },
        {
            "id": "2",
            "time": "24ms"
            ...
        }
    ]
}
Пример результата в XML:

Copy
<root>
    <thread id="1" time="42ms">
        <method name="MyMethod" time="15ms" class="Foo">
            <method name="InnerMethod" time="10ms" class="Bar"/>
        </method>
        ...
    </thread>
    <thread id="2" time="24ms">
        ...
    </thread>
</root>
Готовый результат (полученный JSON и XML) должен выводиться в консоль и записываться в файл. Для данных классов необходимо разработать общий интерфейс, допустимо создать один переиспользуемый класс, не зависящий от того, куда должен выводиться результат (см. Общие ошибки).

Код лабораторной работы должен состоять из трех проектов:

Основная часть библиотеки, реализующая измерение и форматирование результатов.

Модульные тесты для основной части библиотеки.

Консольное приложение, содержащее классы для вывода результатов в консоль и файл, демонстрирующее общий случай работы библиотеки (в многопоточном режиме при трассировке вложенных методов).






Лаба 2: Faker

Необходимо реализовать генератор DTO (объектов для переноса данных) со случайными тестовыми данными:

Copy
var faker = new Faker();
Foo foo = faker.Create<Foo>();
Bar bar = faker.Create<Bar>();
При создании объекта следует использовать конструктор, а также публичные поля и свойства с публичными сеттерами. Следует учитывать сценарии, когда у класса только приватный конструктор, несколько конструкторов, конструктор с параметрами и публичные поля/свойства.

Заполнение должно быть рекурсивным (если полем DTO является другой DTO, то он также должен быть создан с помощью Faker). Логика определения, что является DTO, на усмотрение автора.

Реализовать генераторы случайных значений для базовых типов-значений (int, long, double, float, etc), строк, одного любого системного класса, который можно встретить в DTO, на выбор (дата/время, url, etc), коллекций объектов всех перечисленных типов (поддержка разновидностей IEnumerable<T>, List<T>, IList<T>, ICollection<T>, T[] на усмотрение автора, минимум один вариант из приведенных);

Выделить как минимум 2 базовых генератора в отдельные подключаемые модули (плагины), которые будут загружаться на старте приложения.

Предусмотреть учет циклических зависимостей:

Copy
class A
{
    public B { get; set; }
}

class B
{
    public C { get; set; }
}

class C
{
    public A { get; set; } // циклическая зависимость, 
                           // может быть на любом уровне вложенности
}
Предусмотреть обработку типов, которые не являются DTO, и для которых нет генератора. Их наличие не должно приводить к исключениям во время выполнения.

Задание со звездочкой
Настройка генерируемых случайных значений для конкретного поля путем передачи собственного генератора для конкретного поля/свойства:

Copy
var config = new FakerConfig();
// настройка может иметь и другой API на усмотрение автора 
// (см. ограничение далее по заданию)
config.Add<Foo, string, CityGenerator>(foo => foo.City); 
var faker = new Faker(config);
Foo foo = faker.Create<Foo>(); // при заполнении свойства City должен использоваться CityGenerator
Ограничение: задавать имя свойства/поля в виде строки (явно или с помощью оператора nameof) запрещено, следует использовать деревья выражений: https://docs.microsoft.com/en-us/dotnet/csharp/programming-guide/concepts/expression-trees/.

Настройка должна работать и для неизменяемых объектов, свойства которых не имеют публичного доступа для записи, а создание выполняется через конструктор:

Copy
public class Person
{
   public string Name { get; }
   
   public Person(string name)
   {
      Name = name;
   }
}
Если для такого объекта вы задаете собственный генератор для поля Name config.Add<Person, string, NameGenerator>(p => p.Name), то он должен использоваться при при генерации параметра name для конструктора. При обработке такой ситуации достаточно анализировать имена и типы параметров конструктора, предполагая, что его реализация тривиальна (параметры присваиваются свойствам с соответствующими именами).






Лаба 3: Assembly Browser

Необходимо реализовать графическую утилиту с использованием WPF для просмотра информации о составе произвольной .NET сборки. 

Содержимое загруженной сборки должно быть представлено в иерархическом виде (элемент управления TreeView):

пространства имен; 

типы данных; 

поля, свойства и методы (информация о методах помимо имени должна включать сигнатуру, о полях и свойствах - тип).

Обязательным является применение MVVM, а также использование INotifyPropertyChanged и ICommand.

Код лабораторной работы должен состоять из трех проектов:

библиотека, выполняющая сбор информации о сборке и построение удобной для отображения структуры данных;

модульные тесты для главной библиотеки;

WPF-приложение, отображающее полученные данные о сборке.

Задание со звездочкой
При построении дерева сборки необходимо учитывать объявленные в ней методы расширения (extension methods) и отображать их в составе класса, для которого объявлен метод (а не в составе статического класса с методами расширения), с соответствующей пометкой.






Лаба 4: Tests Generator

Необходимо реализовать многопоточный генератор шаблонного кода тестовых классов для одной из библиотек для тестирования (NUnit, xUnit, MSTest) по тестируемым классам.

Входные данные: 

список файлов, для классов из которых необходимо сгенерировать тестовые классы;

путь к папке для записи созданных файлов;

ограничения на секции конвейера  (см. далее).

Выходные данные:

файлы с тестовыми классами (по одному тестовому классу на файл, вне зависимости от того, как были расположены тестируемые классы в исходных файлах);

все сгенерированные тестовые классы должны компилироваться при включении в отдельный проект, в котором имеется ссылка на проект с тестируемыми классами;

все сгенерированные тесты должны завершаться с ошибкой.

Генерация должна выполняться в конвейерном режиме "производитель-потребитель" и состоять из трех этапов: 

параллельная загрузка исходных текстов в память (с ограничением количества файлов, загружаемых за раз);

генерация тестовых классов в многопоточном режиме (с ограничением максимального количества одновременно обрабатываемых задач); 

параллельная запись результатов на диск (с ограничением количества одновременно записываемых файлов).

При реализации использовать 
async/await
 и асинхронный API. Для реализации конвейера можно использовать Dataflow API:

https://docs.microsoft.com/en-us/dotnet/standard/parallel-programming/dataflow-task-parallel-library

https://docs.microsoft.com/en-us/dotnet/standard/parallel-programming/walkthrough-creating-a-dataflow-pipeline

Главный метод генератора должен возвращать Task и не выполнять никаких ожиданий внутри (блокирующих вызовов 
task.Wait()
, 
task.Result
, etc). Для ввода-вывода также необходимо использовать асинхронный API (https://docs.microsoft.com/en-us/dotnet/standard/io/asynchronous-file-i-o).

Необходимо сгенерировать по одному пустому тесту на каждый публичный метод тестируемого класса

Пример сгенерированного файла для NUnit:

Copy
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using MyCode;

namespace MyCode.Tests
{
    [TestFixture]
    public class MyClassTests
    {
        [Test]
        public void FirstMethodTest()
        {
            Assert.Fail("autogenerated");
        }

        [Test]
        public void SecondMethodTest()
        {
            Assert.Fail("autogenerated");
        }
        ...
    }
}
Для синтаксического разбора и генерации исходного кода следует использовать Roslyn:

https://github.com/dotnet/roslyn

http://roslynquoter.azurewebsites.net/

Код лабораторной работы должен состоять из трех проектов:

библиотека для генерации тестовых классов, содержащая логику по разбору исходного кода и многопоточной генерации классов;

модульные тесты для главной библиотеки;

консольная программа, содержащая логику по чтению входных данных, загрузке исходных файлов в память и записи результатов работы (сгенерированных тестовых классов) в файлы.

Задание со звездочкой
Необходимо сделать генератор более "умным" путем учёта структуры тестируемого класса:

если тестируемый класс принимает через конструктор зависимости по интерфейсам, то в тестовом классе необходимо объявить метод SetUp, в котором создать экземпляр тестируемого класса и Mock-объекты (с помощью Moq или аналогов) всех необходимых ему зависимостей, сохранить их в поля тестового класса для использования в тестах, и передать в конструктор создаваемого тестируемого класса;

для простоты анализ параметров конструктора тестируемого класса достаточно выполнять по именам и полагаться на соглашение об именовании интерфейсов (комплексный анализ проекта/решения, к которому относится тестируемый класс, выполнять не обязательно);

необходимо сгенерировать по одному шаблонному тесту на каждый публичный метод тестируемого класса и создать шаблоны для Arrange (подготовка теста), Act (вызов тестируемого кода), Assert (проверка результата) секций метода;

секция Arrange должна содержать объявление переменных со значениями по умолчанию по входным данным тестируемого метода;

секция Act должна содержать вызов тестируемого метода с передачей ему аргументов, объявленных в Arrange, и сохранение результата метода в переменную actual;

секция Assert должна содержать объявление переменной expected с типом, соответствующим возвращаемому значению метода, и одну проверку на равенство actual и expected;

процедура генерации шаблонов для void методов и для классов, которые принимают в конструктор не только зависимости по интерфейсам, на усмотрение автора, 

приветствуется разумная обработка заданных случаев, но это не является обязательным, пропускать и вообще не обрабатывать такие классы/методы нельзя.

Пример результата работы усовершенствованного генератора для NUnit и Moq:

Copy
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using Moq;
using MyCode;

namespace MyCode.Tests
{
    [TestFixture]
    public class MyClassTests
    {
    	private MyClass _myClassUnderTest;
		private Mock<IDependency> _dependency;

    	[SetUp]
    	public void SetUp()
    	{
    		_dependency = new Mock<IDependency>();
    	 	_myClassUnderTest = new MyClass(_dependency.Object);
    	}
    	
    	
        [Test]
        public void MethodTest()
        {
            // Arrange (комментарии в сгенерированном коде не требуются)
            int number = 0;
            string s = "";
            Foo foo = null;
            
            // Act
            int actual = _myClassUnderTest.MyMethod(number, s, foo);

            // Assert
            int expected = 0;
            Assert.That(actual, Is.EqualTo(expected));
            Assert.Fail("autogenerated");
        }
    }
}






Лаба 5( Не сдавалась, просто нашел где-то:) ): Dependency Injection Container

Необходимо реализовать простой Dependency Injection контейнер.

Dependency Injection контейнер — это обобщенная и конфигурируемая фабрика объектов. Типы данных, объекты реализации которых может создавать DI контейнер, далее будем называть зависимостями.

Контейнер должен позволять регистрировать зависимости в формате: Тип интерфейса (TDependency) -> Тип реализации (TImplementation), где TDependency — любой ссылочный тип данных, а TImplementation — не абстрактный класс, совместимый с TDependency, объект которого может быть создан.

Контейнер должен быть отделен от своей конфигурации: сначала выполняется создание конфигурации и регистрация в нее зависимостей, а затем создание на ее основе контейнера. Должна обеспечиваться валидация конфигурации контейнера в момент создания контейнера.

Copy
// иллюстрация вышесказанного
// конкретный API регистрации/получения зависимостей на усмотрение автора
var dependencies = new DependenciesConfiguration();
dependencies.Register<IService1, Service1>();
dependencies.Register<AbstractService2, Service2>();

// тип зависимости может совпадать с типом реализации
// иногда это называют регистрацией "as self":
dependencies.Register<Service3, Service3>();
 
var provider = new DependencyProvider(dependencies);
var service1 = provider.Resolve<IService1>();
...
Внедрение зависимостей должно осуществляться через конструктор. Создание зависимостей должно выполняться рекурсивно, то есть если TImplementation имеет свои зависимости, а каждая из его зависимостей — свои (и т. д.), то контейнер должен создать их все:

Copy
interface IService {}
class ServiceImpl : IService
{
    public ServiceImpl(IRepository repository) // ServiceImpl зависит от IRepository
    {
        ...
    }
}

interface IRepository{}
class RepositoryImpl : IRepository
{
    public RepositoryImpl(){} // может иметь свои зависимости, опустим для простоты
}

...

// конфигурация и использование контейнера
var dependencies = new DependenciesConfiguration();
dependencies.Register<IService, ServiceImpl>();
dependencies.Register<IRepository, RepositoryImpl>();
 
var provider = new DependencyProvider(dependencies);

// должен быть создан ServiceImpl (реализация IService), в конструктор которому передана
// RepositoryImpl (реализация IRepository)
var service1 = provider.Resolve<IService>(); 
...
Необходимо реализовать два варианта времени жизни зависимостей (задается при регистрации зависимости): 

instance per dependency — каждый новый запрос зависимости из контейнера приводит к созданию нового объекта;

singleton — на все запросы зависимостей возвращается один экземпляр объекта (следует учитывать параллельные запросы в многопоточной среде).

Необходимо учитывать ситуацию наличия нескольких реализаций для одной зависимости и предусмотреть способ получения сразу всех реализаций. Например:

Copy
dependencies.Register<IService, ServiceImpl1>();
dependencies.Register<IService, ServiceImpl2>();
var provider = new DependencyProvider(dependencies);
IEnumerable<IService> services = provider.Resolve<IEnumerable<IService>>();
// ↑ должен вернуться IEnumerable с ServiceImpl1 и ServiceImpl2
Таким же образом IEnumerable<IService> должен создаваться, если он присутствует в конструкторе другого класса.

Зависимость может иметь шаблонный тип, в частности, тип, который влияет на конкретные типы ее зависимостей:

Copy
interface IService<TRepository> where TRepository : IRepository
{
...
}

class ServiceImpl<TRepository> : IService<TRepository> 
    where TRepository : IRepository
{
    public ServiceImpl(TRepository repository)
    {
    ...
    }
    ...
}
В обычном варианте регистрация таких зависимостей визуально не отличается от не шаблонных:

Copy
dependencies.Register<IRepository, MySqlRepository>();
dependencies.Register<IService<IRepository>, ServiceImpl<IRepository>>();
Однако помимо этого должна быть доступна регистрация подобных зависимостей с помощью open generics:

Copy
dependencies.Register(typeof(IService<>), typeof(ServiceImpl<>));
Описанная зависимость является параметризованной: тип generic-параметра зависимости определяется только в момент запроса:

Copy
provider.Resolve<IService<IMySqlRepository>>()
// при создании ServiceImpl<TRepository> должен быть создана зависимость IMySqlRepository 
// (объект класса, зарегистрированный в качестве реализации IMySqlRepository)
// и передана в конструктор
Достаточно реализовать параметризованные зависимости первого порядка, то есть когда open generic непосредственно является типом зависимости, а не параметром другого шаблона:

Copy
// open generics второго порядка
// поддержка таких случаев НЕ ТРЕБУЕТСЯ
// (код носит иллюстративный характер, такого синтаксиса нет, типы необходимо создавать через 
// reflection вручную)
dependencies.Register(typeof(ICommand<IService<>>), typeof(MyCommand<ServiceImpl<>>));
Код лабораторной работы должен состоять из двух проектов:

Dependency Injection контейнер;

модульные тесты.

Проверка работоспособности контейнера должна быть выполнена с помощью модульных тестов. Использовать вспомогательный проект с консольной программой запрещено.

Задание со звездочкой
Добавить поддержку именованных зависимостей:

Copy
enum ServiceImplementations
{
    First,
    Second
}

dependencies.Register<IService, FirstImplementation>(ServiceImplementations.First);
dependencies.Register<IService, SecondImplementation>(ServiceImplementations.Second);
...
// получение напрямую
FirstImplementation first = container.Resolve<IService>(ServiceImplementations.First);
SecondImplementation second = container.Resolve<IService>(ServiceImplementations.Second);
...
// получение в конструкторе
public SomeAnotherService([DependencyKey(ServiceImplementations.Second)] IService service)
{
...
}
Именованные зависимости позволяют различать несколько реализаций одного интерфейса, когда это необходимо (в дополнение к возможности получения сразу всех реализаций). 

Конкретный API получения именованных зависимостей на усмотрение автора, однако обязательна реализация явного получения через Resolve и в конструкторе. 





Условия: https://labs-dnizov.gitbook.io/oot/spp-ch.1