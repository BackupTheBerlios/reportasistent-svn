<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
    
    
    <!-- definovani klice - dulezite kvuli hledani elementu s danym ID v celem dokumentu -->
    <xsl:key name="attribute_id" match="ti_attribute" use="@id" />
    
    <!-- nastaveni jazyka (defaultne cz) -->
	<xsl:variable name="lng">cz</xsl:variable>

    
        
	
	<xsl:template match="hyp_cf">
				
				<element_attributes>
				
		
					<!-- vygenerovani atributu -->
				
					<xsl:apply-templates select="@*"/>

					
					
					<!-- vygenerovani hodnot kontingencni tabulky -->
				
				
					<xsl:variable name="kategorie" >	
						<xsl:value-of select="@attributes" />
					</xsl:variable>
				
				
				
				
				   
				    <xsl:for-each select="r/c">  <!-- cyklus pres polozky radku-->
				   		<xsl:variable name="cislo_sloupce" select="position()" />
				   		<xsl:variable name="jmeno" >
				   				<xsl:text>Tab(</xsl:text>
				   				<xsl:value-of select="key('attribute_id' , $kategorie)/ti_category[$cislo_sloupce]/@value" />
				   				<xsl:text>)</xsl:text>
				   		</xsl:variable>
				   	
		
						<attribute name="{$jmeno}" value="{@val}" />
				   
				    </xsl:for-each>
				   
				</element_attributes>
	</xsl:template>


	
	
	
	
	
	
	
	
	
	<!-- vypise vsechny atributy krome cedentu-->
	
	<xsl:template match="@*">
	
	
		<!-- labely polozek-->
		<xsl:variable name="label">
			<xsl:choose>
			
				<!-- nezavisle na jazyce -->
				
				<xsl:when test="name()='sum'">
					<xsl:text>Sum</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='min'">
					<xsl:text>Min</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='max'">
					<xsl:text>Max</xsl:text>
				</xsl:when>
						
				<xsl:when test="name()='v'">
					<xsl:text>Variation ratio : 1-f(modal) </xsl:text>
				</xsl:when>
						
				<xsl:when test="name()='nom_var'">
					<xsl:text>Nominal variation : suma(f(i)*(1-f(i))) * K/(K-1) </xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='dor_var'">
					<xsl:text>Discrete ordinary variation : 2*suma(F(i)*(1-F(i))* 2/(K-1)</xsl:text>
				</xsl:when>
							
				
				
				
				<!-- cesky -->
				
				<xsl:when test="$lng='cz'">    
						<xsl:choose>
							<xsl:when test="name()='db_name'">
								<xsl:text>Databáze</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='matrix_name'">
								<xsl:text>Datová matice</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_name'">
								<xsl:text>Jméno úlohy</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='avg_a'">
								<xsl:text>Aritmetický průměr kardinálních hodnot</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='avg_g'">
								<xsl:text>Geometrický průměr kardinálních hodnot</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='var'">
								<xsl:text>Variance kardinálních hodnot</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='st_dev'">
								<xsl:text>Standardní deviace kardinálních hodnot</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='skew'">
								<xsl:text>Skewness (šikmost) kardinálních hodnot</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='asym'">
								<xsl:text>Koeficient asymetrie kardinálních hodnot</xsl:text>
							</xsl:when>
							
							<xsl:otherwise>
								<xsl:value-of select="name()"/>
							</xsl:otherwise>
						</xsl:choose>
				</xsl:when>
				
				
				<!-- english-->
				
				<xsl:when test="$lng='en'">	
						<xsl:choose>
							<xsl:when test="name()='db_name'">
								<xsl:text>Database</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='matrix_name'">
								<xsl:text>Data matrix</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_name'">
								<xsl:text>Task name</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='avg_a'">
								<xsl:text>Arithmetic average of cardinal values</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='avg_g'">
								<xsl:text>Geometric average of cardinal values</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='var'">
								<xsl:text>Variance of cardinal values</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='st_dev'">
								<xsl:text>Standard deviation of cardinal values</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='skew'">
								<xsl:text>Skewness of cardinal values</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='asym'">
								<xsl:text>Asymetry coeficient of cardinal values</xsl:text>
							</xsl:when>
							
							<xsl:otherwise>
								<xsl:value-of select="name()"/>
							</xsl:otherwise>
						</xsl:choose>	
				</xsl:when>
				
				<!-- jinak se pouzije nazev XML atributu-->
				
				<xsl:otherwise>
					<xsl:value-of select="name()"/>
				</xsl:otherwise>
				
			</xsl:choose>
		</xsl:variable>
			<!-- end of: labely polozek-->
	
	
					<attribute name="{name()}" value="{.}" label="{$label}" />
					
	</xsl:template>
	
	



	<!-- zpracovani cedentu-->
	
	<xsl:template match="@attributes | @condition">
		
		<xsl:apply-templates select="id(.)" mode="values" />		

	</xsl:template>
	
	
	

	

	<!-- boolske literaly -> cedent -->
	<xsl:template match="ti_cedent" mode="values">		
    	<xsl:variable name="hodnota_cedentu">
    		<xsl:apply-templates select="ti_literal" mode="values"/>
    	</xsl:variable>
    	<xsl:text disable-output-escaping="yes">
					</xsl:text>		
    	<attribute name="{@type}" value="{$hodnota_cedentu}" />	
	</xsl:template>
	
	
	
	<!-- kategorialni cedent -->
	<xsl:template match="ti_attribute" mode="values">
		<xsl:text disable-output-escaping="yes">
					</xsl:text>		
    	<attribute name="{@type}" value="{@quant}" />
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
