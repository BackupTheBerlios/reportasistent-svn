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
        <attribute name="attributes" label="Attributes" />
        <attribute name="condition"  label="Condition"/>

        <!-- vychozi hodnoty:
                numeric_sort="false"
                default_sort_direction="ascending"     -->

        <!-- nezavisle na jazyce -->
        <attribute name="sum" label="Sum" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="min" label="Min" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="max" label="Max" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="v" label="Variation ratio" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="nom_var" label="Nominal variation" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="dor_var" label="Discrete ordinary variation" numeric_sort="true" default_sort_direction="descending"/>

        <xsl:choose>

          <!-- english -->
          <xsl:when test="$lng='en'">
            <attribute name="avg_a" label="Arithmetic average of cardinal values" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="avg_g" label="Geometric average of cardinal values" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="var" label="Variance of cardinal values" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="st_dev" label="Standard deviation of cardinal values" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="skew" label="Skewness of cardinal values" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="asym" label="Asymetry coeficient of cardinal values" numeric_sort="true" default_sort_direction="descending"/>
          </xsl:when>

          <!-- cesky-->
          <xsl:when test="$lng='cz'">
            <attribute name="avg_a" label="Aritmetický průměr kardinálních hodnot" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="avg_g" label="Geometrický průměr kardinálních hodnot" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="var" label="Variance kardinálních hodnot" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="st_dev" label="Standardní deviace kardinálních hodnot" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="skew" label="Skewness (šikmost) kardinálních hodnot" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="asym" label="Koeficient asymetrie kardinálních hodnot" numeric_sort="true" default_sort_direction="descending"/>
          </xsl:when>
        </xsl:choose>


      </attributes>

      <values>
        <xsl:apply-templates select="hyp_cf" mode="values"/>
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
	<xsl:template match="@attributes | @condition" mode="values">
	
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
