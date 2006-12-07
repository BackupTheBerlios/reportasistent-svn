<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">

  <!-- nastaveni jazyka (defaultne en) -->
  <xsl:variable name="lng">en</xsl:variable>


  <xsl:template match="/active_list">

    <dialog_data>
      <attributes>
        <attribute name="id" label="id" />

        <xsl:choose>

          <!-- english -->
          <xsl:when test="$lng='en'">
            <attribute name="db_name" label="Database" />
            <attribute name="matrix_name" label="Data matrix" />
            <attribute name="task_name" label="Task name" />
          </xsl:when>

          <!-- cesky-->
          <xsl:when test="$lng='cz'">
            <attribute name="db_name" label="Databáze" />
            <attribute name="matrix_name" label="Datová matice" />
            <attribute name="task_name" label="Jméno úlohy" />
          </xsl:when>
        </xsl:choose>

        <!-- nezavisle na jazyce -->
        <attribute name="row_attributes" label="Row attributes" />
        <attribute name="column_attributes" label="Column attributes"/>
        <attribute name="condition"  label="Condition"/>
        <attribute name="set1"  label="First set"/>
        <attribute name="set2"  label="Second set"/>
        
        <!-- vychozi hodnoty:
                numeric_sort="false"
                default_sort_direction="ascending"     -->

        <!-- nezavisle na jazyce -->
        <attribute name="sum1" label="Sum 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="min1" label="Min 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="max1" label="Max 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="chi_sq1" label="Chi-square test 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="fnc_s1" label="FncS (sum) 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="fnc_r1" label="FncR (row) 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="h_c1" label="H(C) 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="h_r1" label="H(R) 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="h_c_r1" label="H(C|R) 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="mi1" label="Mutual information MI(C,R) 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="aic1" label="Asymetric information coefficient AIC(R,C) 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="kend1" label="Kendall coefficient 1" numeric_sort="true" default_sort_direction="descending"/>

        <attribute name="sum2" label="Sum 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="min2" label="Min 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="max2" label="Max 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="chi_sq2" label="Chi-square test 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="fnc_s2" label="FncS (sum) 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="fnc_r2" label="FncR (row) 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="h_c2" label="H(C) 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="h_r2" label="H(R) 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="h_c_r2" label="H(C|R) 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="mi2" label="Mutual information MI(C,R) 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="aic2" label="Asymetric information coefficient AIC(R,C) 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="kend2" label="Kendall coefficient 2" numeric_sort="true" default_sort_direction="descending"/>

        <attribute name="da_sum" label="DA-Sum" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="da_min" label="DA-Min" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="da_max" label="DA-Max" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="dr_sum" label="D%-Sum" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="dr_min" label="D%-Min" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="dr_max" label="D%-Max" numeric_sort="true" default_sort_direction="descending"/>

        
      </attributes>

      <values>
        <xsl:apply-templates select="hyp_sdkl" mode="values"/>
      </values>

    </dialog_data>


  </xsl:template>




  <!-- vypise hodnoty -->
  <xsl:template match="node()" mode="values">


    <xsl:text disable-output-escaping="yes">
		&lt;value </xsl:text>
    <xsl:apply-templates select="@*" mode="values"/>
    <xsl:text disable-output-escaping="yes">/&gt;</xsl:text>


  </xsl:template>



  <!-- naplni hodnotu -->
  <xsl:template match="@*" mode="values">

    <xsl:value-of select="name()"/>

    <xsl:text disable-output-escaping="yes">="</xsl:text>

    <xsl:value-of select="."/>




    <!-- volani JScriptu

    <xsl:text>___</xsl:text>
    <xsl:value-of select="dedek:hex(1245678)"/>

 volani JScriptu konec -->





    <xsl:text disable-output-escaping="yes">" </xsl:text>

    <xsl:apply-templates select="@*"/>
  </xsl:template>



  <!-- naplni hodnoty cedentu-->
  <xsl:template match="@row_attributes | @column_attributes | @condition | @set1 | @set2" mode="values">

    <xsl:value-of select="name()"/>

    <xsl:text disable-output-escaping="yes">="</xsl:text>

    <xsl:apply-templates select="id(.)" mode="values"/>

    <xsl:text disable-output-escaping="yes">" </xsl:text>

    <xsl:apply-templates select="@*"/>
  </xsl:template>


  <!-- boolske literaly -> cedent -->
  <xsl:template match="ti_cedent" mode="values">
    <xsl:apply-templates select="ti_literal" mode="values"/>
  </xsl:template>

  <!--  kategorialni cedenty -->
  <xsl:template match="ti_attribute" mode="values">
    <xsl:if test="position()!=1">
      <xsl:text disable-output-escaping="yes"> ; </xsl:text>
    </xsl:if>


    <xsl:value-of select="@quant"/>
  </xsl:template>


  <!-- preformatuje boolsky literal -->
  <xsl:template match="ti_literal" mode="values">

    <xsl:if test="position()!=1">
      <xsl:text disable-output-escaping="no"> &amp; </xsl:text>
    </xsl:if>


    <xsl:value-of select="@quant"/>
    <xsl:text disable-output-escaping="yes">(</xsl:text>
    <xsl:value-of select="@value"/>
    <xsl:text disable-output-escaping="yes">)</xsl:text>
  </xsl:template>







</xsl:stylesheet>
