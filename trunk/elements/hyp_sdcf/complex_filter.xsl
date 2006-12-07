<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">

  <!-- nastaveni jazyka (defaultne cz) -->
  <xsl:variable name="lng">cz</xsl:variable>


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
        <attribute name="set1"  label="First set"/>
        <attribute name="set2"  label="Second set"/>

        <!-- vychozi hodnoty:
                numeric_sort="false"
                default_sort_direction="ascending"     -->

        <!--hodnoty kvantifikatoru - First set-->
        
        <!-- nezavisle na jazyce -->
        <attribute name="sum1" label="Sum 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="min1" label="Min 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="max1" label="Max 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="v1" label="Variation ratio 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="nom_var1" label="Nominal variation 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="dor_var1" label="Discrete ordinary variation 1" numeric_sort="true" default_sort_direction="descending"/>

        <xsl:choose>

          <!-- english -->
          <xsl:when test="$lng='en'">
            <attribute name="avg_a1" label="Arithmetic average of cardinal values 1" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="avg_g1" label="Geometric average of cardinal values 1" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="var1" label="Variance of cardinal values 1" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="st_dev1" label="Standard deviation of cardinal values 1" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="skew1" label="Skewness of cardinal values 1" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="asym1" label="Asymetry coeficient of cardinal values 1" numeric_sort="true" default_sort_direction="descending"/>
          </xsl:when>

          <!-- cesky-->
          <xsl:when test="$lng='cz'">
            <attribute name="avg_a1" label="Aritmetický průměr kardinálních hodnot 1" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="avg_g1" label="Geometrický průměr kardinálních hodnot 1" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="var1" label="Variance kardinálních hodnot 1" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="st_dev1" label="Standardní deviace kardinálních hodnot 1" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="skew1" label="Skewness (šikmost) kardinálních hodnot 1" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="asym1" label="Koeficient asymetrie kardinálních hodnot 1" numeric_sort="true" default_sort_direction="descending"/>
          </xsl:when>
        </xsl:choose>

        <!--hodnoty kvantifikatoru - Second set-->

        <!-- nezavisle na jazyce -->
        <attribute name="sum2" label="Sum 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="min2" label="Min 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="max2" label="Max 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="v2" label="Variation ratio 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="nom_var2" label="Nominal variation 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="dor_var2" label="Discrete ordinary variation 2" numeric_sort="true" default_sort_direction="descending"/>

        <xsl:choose>

          <!-- english -->
          <xsl:when test="$lng='en'">
            <attribute name="avg_a2" label="Arithmetic average of cardinal values 2" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="avg_g2" label="Geometric average of cardinal values 2" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="var2" label="Variance of cardinal values 2" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="st_dev2" label="Standard deviation of cardinal values 2" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="skew2" label="Skewness of cardinal values 2" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="asym2" label="Asymetry coeficient of cardinal values 2" numeric_sort="true" default_sort_direction="descending"/>
          </xsl:when>

          <!-- cesky-->
          <xsl:when test="$lng='cz'">
            <attribute name="avg_a2" label="Aritmetický průměr kardinálních hodnot 2" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="avg_g2" label="Geometrický průměr kardinálních hodnot 2" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="var2" label="Variance kardinálních hodnot 2" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="st_dev2" label="Standardní deviace kardinálních hodnot 2" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="skew2" label="Skewness (šikmost) kardinálních hodnot 2" numeric_sort="true" default_sort_direction="descending"/>
            <attribute name="asym2" label="Koeficient asymetrie kardinálních hodnot 2" numeric_sort="true" default_sort_direction="descending"/>
          </xsl:when>
        </xsl:choose>

        <!--hodnoty kvantifikatoru - rozdily mnozin-->
        <attribute name="da_sum" label="DA-Sum" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="da_min" label="DA-Min" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="da_max" label="DA-Max" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="dr_sum" label="D%-Sum" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="dr_min" label="D%-Min" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="dr_max" label="D%-Max" numeric_sort="true" default_sort_direction="descending"/>

      </attributes>

      <values>
        <xsl:apply-templates select="hyp_sdcf" mode="values"/>
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

    
    
    

    
    
    <xsl:text disable-output-escaping="yes">" </xsl:text>

    	<xsl:apply-templates select="@*"/>
	</xsl:template>

	
	
	<!-- naplni hodnoty cedentu-->
	<xsl:template match="@attributes | @condition | @set1 | @set2" mode="values">
	
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
