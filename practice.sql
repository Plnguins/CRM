--
-- PostgreSQL database dump
--

-- Dumped from database version 14.3
-- Dumped by pg_dump version 14.3

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: advertisement; Type: TABLE; Schema: public; Owner: practice
--

CREATE TABLE public.advertisement (
    id integer NOT NULL,
    source character varying NOT NULL,
    budget integer NOT NULL,
    comments text
);


ALTER TABLE public.advertisement OWNER TO practice;

--
-- Name: TABLE advertisement; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON TABLE public.advertisement IS 'Рекламные компании организации';


--
-- Name: COLUMN advertisement.id; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.advertisement.id IS 'ID рекламной компании';


--
-- Name: COLUMN advertisement.source; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.advertisement.source IS 'Место размещения рекламы';


--
-- Name: COLUMN advertisement.budget; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.advertisement.budget IS 'Бюджет компании';


--
-- Name: COLUMN advertisement.comments; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.advertisement.comments IS 'Комментарии';


--
-- Name: advertisement_id_seq; Type: SEQUENCE; Schema: public; Owner: practice
--

ALTER TABLE public.advertisement ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.advertisement_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- Name: client; Type: TABLE; Schema: public; Owner: practice
--

CREATE TABLE public.client (
    id integer NOT NULL,
    surname character varying,
    name character varying NOT NULL,
    patronymic character varying NOT NULL,
    email character varying NOT NULL,
    phone character varying NOT NULL,
    sex character varying,
    city character varying
);


ALTER TABLE public.client OWNER TO practice;

--
-- Name: TABLE client; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON TABLE public.client IS 'Клиенты компании';


--
-- Name: COLUMN client.id; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.client.id IS 'ID клиента';


--
-- Name: COLUMN client.surname; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.client.surname IS 'Фамилия клиента';


--
-- Name: COLUMN client.name; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.client.name IS 'Имя клиента';


--
-- Name: COLUMN client.patronymic; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.client.patronymic IS 'Отчество клиента';


--
-- Name: COLUMN client.email; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.client.email IS 'Электронная почта клиента';


--
-- Name: COLUMN client.phone; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.client.phone IS 'Телефон клиента';


--
-- Name: COLUMN client.sex; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.client.sex IS 'Пол клиента';


--
-- Name: COLUMN client.city; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.client.city IS 'Город клиента';


--
-- Name: client_id_seq; Type: SEQUENCE; Schema: public; Owner: practice
--

ALTER TABLE public.client ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.client_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- Name: comments; Type: TABLE; Schema: public; Owner: practice
--

CREATE TABLE public.comments (
    id integer NOT NULL,
    deal integer NOT NULL,
    date date DEFAULT now() NOT NULL
);


ALTER TABLE public.comments OWNER TO practice;

--
-- Name: TABLE comments; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON TABLE public.comments IS 'Комментарии к сделкам';


--
-- Name: COLUMN comments.id; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.comments.id IS 'ID комментария';


--
-- Name: COLUMN comments.deal; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.comments.deal IS 'ID сделки, к которому относится комментарий';


--
-- Name: COLUMN comments.date; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.comments.date IS 'Дата комментария';


--
-- Name: comments_id_seq; Type: SEQUENCE; Schema: public; Owner: practice
--

ALTER TABLE public.comments ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.comments_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- Name: deal; Type: TABLE; Schema: public; Owner: practice
--

CREATE TABLE public.deal (
    id integer NOT NULL,
    laptop integer NOT NULL,
    cost integer NOT NULL,
    client integer NOT NULL,
    status text DEFAULT 'Создан'::text,
    date date DEFAULT now(),
    seller integer NOT NULL,
    rate integer
);


ALTER TABLE public.deal OWNER TO practice;

--
-- Name: TABLE deal; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON TABLE public.deal IS 'Сделки компании';


--
-- Name: COLUMN deal.id; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.deal.id IS 'ID сделки';


--
-- Name: COLUMN deal.laptop; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.deal.laptop IS 'ID ноутбука';


--
-- Name: COLUMN deal.cost; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.deal.cost IS 'Цена продажи';


--
-- Name: COLUMN deal.client; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.deal.client IS 'ID клиента';


--
-- Name: COLUMN deal.date; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.deal.date IS 'Дата создания сделки';


--
-- Name: COLUMN deal.seller; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.deal.seller IS 'ID отвественного сотрудника';


--
-- Name: COLUMN deal.rate; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.deal.rate IS 'Оценка покупателя';


--
-- Name: deal_id_seq; Type: SEQUENCE; Schema: public; Owner: practice
--

ALTER TABLE public.deal ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.deal_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- Name: employee; Type: TABLE; Schema: public; Owner: practice
--

CREATE TABLE public.employee (
    id integer NOT NULL,
    surname character varying NOT NULL,
    name character varying NOT NULL,
    second_name character varying NOT NULL,
    login character varying NOT NULL,
    passworrd character varying NOT NULL
);


ALTER TABLE public.employee OWNER TO practice;

--
-- Name: TABLE employee; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON TABLE public.employee IS 'Список сотрудников компании';


--
-- Name: COLUMN employee.id; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.employee.id IS 'ID работника';


--
-- Name: COLUMN employee.surname; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.employee.surname IS 'Фамилия работника';


--
-- Name: COLUMN employee.name; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.employee.name IS 'Имя работника';


--
-- Name: COLUMN employee.second_name; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.employee.second_name IS 'Отчество работника';


--
-- Name: COLUMN employee.login; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.employee.login IS 'Логин работника';


--
-- Name: COLUMN employee.passworrd; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.employee.passworrd IS 'Хеш пароля работника';


--
-- Name: employee_id_seq; Type: SEQUENCE; Schema: public; Owner: practice
--

ALTER TABLE public.employee ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.employee_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- Name: laptop; Type: TABLE; Schema: public; Owner: practice
--

CREATE TABLE public.laptop (
    id integer NOT NULL,
    name character varying NOT NULL,
    income double precision NOT NULL,
    type character varying NOT NULL,
    cpu character varying NOT NULL,
    gpu character varying NOT NULL,
    ram integer NOT NULL,
    rom integer NOT NULL,
    color character varying NOT NULL
);


ALTER TABLE public.laptop OWNER TO practice;

--
-- Name: TABLE laptop; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON TABLE public.laptop IS 'Список ноутбуков';


--
-- Name: COLUMN laptop.id; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.laptop.id IS 'ID ноутбука';


--
-- Name: COLUMN laptop.name; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.laptop.name IS 'Название ноутбука';


--
-- Name: COLUMN laptop.income; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.laptop.income IS 'Желаемая прибыль для ноутбука (в процентах)';


--
-- Name: COLUMN laptop.type; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.laptop.type IS 'Тип ноутбука';


--
-- Name: COLUMN laptop.cpu; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.laptop.cpu IS 'Процессор';


--
-- Name: COLUMN laptop.gpu; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.laptop.gpu IS 'Графический ускоритель';


--
-- Name: COLUMN laptop.ram; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.laptop.ram IS 'Количество оперативной памяти (в МБ)';


--
-- Name: COLUMN laptop.rom; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.laptop.rom IS 'Количество постоянной памяти (в МБ)';


--
-- Name: COLUMN laptop.color; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.laptop.color IS 'Цвет';


--
-- Name: laptop_id_seq; Type: SEQUENCE; Schema: public; Owner: practice
--

ALTER TABLE public.laptop ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.laptop_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- Name: leader; Type: TABLE; Schema: public; Owner: practice
--

CREATE TABLE public.leader (
    id integer NOT NULL,
    employee integer NOT NULL
);


ALTER TABLE public.leader OWNER TO practice;

--
-- Name: TABLE leader; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON TABLE public.leader IS 'Список руководителей';


--
-- Name: COLUMN leader.id; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.leader.id IS 'ID записи';


--
-- Name: COLUMN leader.employee; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.leader.employee IS 'ID сотрудника';


--
-- Name: leader_id_seq; Type: SEQUENCE; Schema: public; Owner: practice
--

ALTER TABLE public.leader ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.leader_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- Name: marketer; Type: TABLE; Schema: public; Owner: practice
--

CREATE TABLE public.marketer (
    id integer NOT NULL,
    employee integer NOT NULL
);


ALTER TABLE public.marketer OWNER TO practice;

--
-- Name: TABLE marketer; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON TABLE public.marketer IS 'Список маркетологов';


--
-- Name: COLUMN marketer.id; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.marketer.id IS 'ID записи';


--
-- Name: COLUMN marketer.employee; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.marketer.employee IS 'ID сотрудника';


--
-- Name: marketer_id_seq; Type: SEQUENCE; Schema: public; Owner: practice
--

ALTER TABLE public.marketer ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.marketer_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- Name: provider; Type: TABLE; Schema: public; Owner: practice
--

CREATE TABLE public.provider (
    id integer NOT NULL,
    name text NOT NULL
);


ALTER TABLE public.provider OWNER TO practice;

--
-- Name: TABLE provider; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON TABLE public.provider IS 'Список поставщиков ноутбуков';


--
-- Name: COLUMN provider.id; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.provider.id IS 'ID поставщика';


--
-- Name: COLUMN provider.name; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.provider.name IS 'Название поставщика';


--
-- Name: provider_id_seq; Type: SEQUENCE; Schema: public; Owner: practice
--

ALTER TABLE public.provider ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.provider_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- Name: seller; Type: TABLE; Schema: public; Owner: practice
--

CREATE TABLE public.seller (
    id integer NOT NULL,
    employee integer NOT NULL
);


ALTER TABLE public.seller OWNER TO practice;

--
-- Name: TABLE seller; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON TABLE public.seller IS 'Список продавцов';


--
-- Name: COLUMN seller.id; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.seller.id IS 'ID записи';


--
-- Name: COLUMN seller.employee; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.seller.employee IS 'ID сотрудника';


--
-- Name: seller_id_seq; Type: SEQUENCE; Schema: public; Owner: practice
--

ALTER TABLE public.seller ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.seller_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- Name: stock; Type: TABLE; Schema: public; Owner: practice
--

CREATE TABLE public.stock (
    id integer NOT NULL,
    laptop integer NOT NULL,
    price integer NOT NULL,
    count integer NOT NULL,
    available integer NOT NULL,
    source integer NOT NULL
);


ALTER TABLE public.stock OWNER TO practice;

--
-- Name: TABLE stock; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON TABLE public.stock IS 'Склад ноутбуков';


--
-- Name: COLUMN stock.id; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.stock.id IS 'ID партии товара';


--
-- Name: COLUMN stock.laptop; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.stock.laptop IS 'ID ноутбука';


--
-- Name: COLUMN stock.price; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.stock.price IS 'Цена покупки';


--
-- Name: COLUMN stock.count; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.stock.count IS 'Количество на складе';


--
-- Name: COLUMN stock.available; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.stock.available IS 'Доступное количество';


--
-- Name: COLUMN stock.source; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.stock.source IS 'ID поставщика';


--
-- Name: stock_id_seq; Type: SEQUENCE; Schema: public; Owner: practice
--

ALTER TABLE public.stock ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.stock_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- Name: stock_manager; Type: TABLE; Schema: public; Owner: practice
--

CREATE TABLE public.stock_manager (
    id integer NOT NULL,
    employee integer NOT NULL
);


ALTER TABLE public.stock_manager OWNER TO practice;

--
-- Name: TABLE stock_manager; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON TABLE public.stock_manager IS 'Список менеджеров по снабжению';


--
-- Name: COLUMN stock_manager.id; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.stock_manager.id IS 'ID записи';


--
-- Name: stock_manager_id_seq; Type: SEQUENCE; Schema: public; Owner: practice
--

ALTER TABLE public.stock_manager ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.stock_manager_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- Name: views; Type: TABLE; Schema: public; Owner: practice
--

CREATE TABLE public.views (
    id bigint NOT NULL,
    source integer,
    deal integer
);


ALTER TABLE public.views OWNER TO practice;

--
-- Name: TABLE views; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON TABLE public.views IS 'Список просмотров';


--
-- Name: COLUMN views.id; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.views.id IS 'ID просмотра';


--
-- Name: COLUMN views.source; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.views.source IS 'ID рекламной компании по которой просмотр';


--
-- Name: COLUMN views.deal; Type: COMMENT; Schema: public; Owner: practice
--

COMMENT ON COLUMN public.views.deal IS 'ID сделки (NULL если не было) для просмотра';


--
-- Name: views_id_seq; Type: SEQUENCE; Schema: public; Owner: practice
--

ALTER TABLE public.views ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.views_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- Name: client Email, phone; Type: CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.client
    ADD CONSTRAINT "Email, phone" UNIQUE (email, phone);


--
-- Name: employee Login; Type: CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.employee
    ADD CONSTRAINT "Login" UNIQUE (login);


--
-- Name: advertisement advertisement_pkey; Type: CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.advertisement
    ADD CONSTRAINT advertisement_pkey PRIMARY KEY (id);


--
-- Name: client client_pkey; Type: CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.client
    ADD CONSTRAINT client_pkey PRIMARY KEY (id);


--
-- Name: comments comments_pkey; Type: CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.comments
    ADD CONSTRAINT comments_pkey PRIMARY KEY (id);


--
-- Name: deal deal_pkey; Type: CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.deal
    ADD CONSTRAINT deal_pkey PRIMARY KEY (id);


--
-- Name: employee employee_pkey; Type: CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.employee
    ADD CONSTRAINT employee_pkey PRIMARY KEY (id);


--
-- Name: laptop laptop_pkey; Type: CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.laptop
    ADD CONSTRAINT laptop_pkey PRIMARY KEY (id);


--
-- Name: leader leader_pkey; Type: CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.leader
    ADD CONSTRAINT leader_pkey PRIMARY KEY (id);


--
-- Name: marketer marketer_pkey; Type: CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.marketer
    ADD CONSTRAINT marketer_pkey PRIMARY KEY (id);


--
-- Name: provider provider_pkey; Type: CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.provider
    ADD CONSTRAINT provider_pkey PRIMARY KEY (id);


--
-- Name: seller seller_pkey; Type: CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.seller
    ADD CONSTRAINT seller_pkey PRIMARY KEY (id);


--
-- Name: stock_manager stock_manager_pkey; Type: CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.stock_manager
    ADD CONSTRAINT stock_manager_pkey PRIMARY KEY (id);


--
-- Name: stock stock_pkey; Type: CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.stock
    ADD CONSTRAINT stock_pkey PRIMARY KEY (id);


--
-- Name: views views_pkey; Type: CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.views
    ADD CONSTRAINT views_pkey PRIMARY KEY (id);


--
-- Name: deal client; Type: FK CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.deal
    ADD CONSTRAINT client FOREIGN KEY (client) REFERENCES public.client(id) NOT VALID;


--
-- Name: views deal; Type: FK CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.views
    ADD CONSTRAINT deal FOREIGN KEY (deal) REFERENCES public.deal(id);


--
-- Name: comments deal; Type: FK CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.comments
    ADD CONSTRAINT deal FOREIGN KEY (deal) REFERENCES public.deal(id);


--
-- Name: marketer employee; Type: FK CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.marketer
    ADD CONSTRAINT employee FOREIGN KEY (employee) REFERENCES public.employee(id);


--
-- Name: seller employee; Type: FK CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.seller
    ADD CONSTRAINT employee FOREIGN KEY (employee) REFERENCES public.employee(id);


--
-- Name: stock_manager employee; Type: FK CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.stock_manager
    ADD CONSTRAINT employee FOREIGN KEY (employee) REFERENCES public.employee(id);


--
-- Name: leader employee; Type: FK CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.leader
    ADD CONSTRAINT employee FOREIGN KEY (employee) REFERENCES public.employee(id);


--
-- Name: deal laptop; Type: FK CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.deal
    ADD CONSTRAINT laptop FOREIGN KEY (laptop) REFERENCES public.laptop(id);


--
-- Name: stock laptop; Type: FK CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.stock
    ADD CONSTRAINT laptop FOREIGN KEY (laptop) REFERENCES public.laptop(id);


--
-- Name: deal seller; Type: FK CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.deal
    ADD CONSTRAINT seller FOREIGN KEY (seller) REFERENCES public.employee(id) NOT VALID;


--
-- Name: views source; Type: FK CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.views
    ADD CONSTRAINT source FOREIGN KEY (source) REFERENCES public.advertisement(id);


--
-- Name: stock source; Type: FK CONSTRAINT; Schema: public; Owner: practice
--

ALTER TABLE ONLY public.stock
    ADD CONSTRAINT source FOREIGN KEY (source) REFERENCES public.provider(id) NOT VALID;


--
-- Name: SCHEMA public; Type: ACL; Schema: -; Owner: practice
--

REVOKE ALL ON SCHEMA public FROM postgres;
REVOKE ALL ON SCHEMA public FROM PUBLIC;
GRANT ALL ON SCHEMA public TO practice;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--

