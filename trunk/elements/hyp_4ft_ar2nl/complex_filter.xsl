<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">

  <!-- nastaveni jazyka (defaultne cz) -->
  <xsl:variable name="lng">en</xsl:variable>


  <xsl:template match="/active_list">



    <dialog_data>
      <attributes>
        <attribute name="id" label="id" />

        <xsl:choose>

          <!-- cesky -->
          <xsl:when test="$lng='en'">
            <attribute name="db_name" label="Database" />
            <attribute name="matrix_name" label="Data matrix" />
            <attribute name="task_name" label="Task name" />
            <attribute name="sentences_count" label="Sentences count" />
          </xsl:when>

          <!-- english-->
          <xsl:when test="$lng='cz'">
            <attribute name="db_name" label="Datab�ze" />
            <attribute name="matrix_name" label="Datov� matice" />
            <attribute name="task_name" label="Jm�no �lohy" />
            <attribute name="sentences_count" label="Nalezen�ch v�t" />
          </xsl:when>
        </xsl:choose>

        <!-- vychozi hodnoty:
                numeric_sort="false"
                default_sort_direction="ascending"     -->

        <!-- nezavisle na jazyce -->
        <attribute name="antecedent" label="Antecedent" />
        <attribute name="succedent" label="Succedent"/>
        <attribute name="condition"  label="Condition"/>
        
        <attribute name="a" label="a" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="b" label="b" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="c" label="c" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="d" label="d" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="conf" label="Confidence" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="d_conf" label="D-Confidence" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="e_conf" label="E-Confidence" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="support" label="Support" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="completeness" label="Completeness" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="avg_diff" label="Average difference" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="low_bnd_imp" label="Lower bound implication" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="up_bnd_imp" label="Upper bound implication" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="low_bnd_dbl_imp" label="Upper bound implication" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="up_bnd_dbl_imp" label="Upper bound double implication" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="low_bnd_eq" label="Lower bound equivalence" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="up_bnd_eq" label="Upper bound equivalence" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="fisher" label="Fisher test" numeric_sort="true" />
        <attribute name="chi_sq" label="Chi-square test" numeric_sort="true" />
        
      </attributes>

      <values>
        <xsl:apply-templates select="hyp_4ft_ar2nl" mode="values"/>
      </values>

    </dialog_data>

    <!--

      <xsl:apply-templates select="hyp_4ft[position()=1]" mode="attributes"/>

      <xsl:element name="values">
      </xsl:element>
		-->

  </xsl:template>




  <!-- vypise hodnoty -->
  <xsl:template match="node()" mode="values">

    <xsl:element name="value">
      <xsl:apply-templates select="@*" mode="values"/>
      <!-- vypsani poctu vygenerovanych vet AR2NL-->
      <xsl:variable name="sentences_count" select="count(sentences/sentence)"/>
      <xsl:attribute name="sentences_count">
        <xsl:value-of select="$sentences_count"/>
      </xsl:attribute>
    </xsl:element>

  </xsl:template>



  <!-- naplni hodnotu cedentu-->
  <xsl:template match="@antecedent | @succedent | @condition" mode="values">


    <xsl:attribute name="{name()}">
      <xsl:apply-templates select="id(.)" mode="values"/>
    </xsl:attribute>


    <xsl:apply-templates select="@*"/>

  </xsl:template>



  <!-- naplni hodnoty atributu krome cedentu a poctu vet -->
  <xsl:template match="@*" mode="values">
    <xsl:attribute name="{name()}">
      <xsl:value-of select="."/>
    </xsl:attribute>
  </xsl:template>






  <!-- literaly -> cedent -->
  <xsl:template match="ti_cedent" mode="values">
    <xsl:apply-templates select="ti_literal" mode="values"/>
  </xsl:template>





  <!-- preformatuje literal -->
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
